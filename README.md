<div align="center">

# 📖 Get Next Line

### Reading a line from a fd is way too tedious

<p>
  <img src="https://img.shields.io/badge/Score-115%2F100-success?style=for-the-badge&logo=42" alt="42 Score"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Language"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License"/>
  <img src="https://img.shields.io/badge/42-Urduliz-000000?style=for-the-badge&logo=42&logoColor=white" alt="42 Urduliz"/>
</p>

*A function that reads and returns one line at a time from a file descriptor, introducing the concept of static variables in C.*

[Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [Implementation](#-implementation-details) • [Testing](#-testing)

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [Function Prototype](#-function-prototype)
- [Implementation Details](#-implementation-details)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [What I Learned](#-what-i-learned)
- [License](#-license)

---

## 🎯 About the Project

**Get Next Line** challenges you to implement a function that reads a file line by line. Each call to `get_next_line()` returns the next line from a file descriptor, making it possible to read text files efficiently without loading the entire content into memory.

### Why Get Next Line?

This project introduces **static variables** - one of the most powerful concepts in C programming:
- **File I/O operations** - Reading large files efficiently
- **Persistent data** - Maintaining context between function calls
- **Buffer management** - Handling partial reads and leftovers
- **Memory optimization** - Reading only what's needed at each call
- **Multiple file descriptors** - Managing state for different sources (bonus)

---

## 🛠️ Installation

### Prerequisites

- **GCC** or **Clang** compiler
- Unix-based system (Linux, macOS)

### Clone and Compile

```bash
# Clone the repository
git clone https://github.com/Z3n42/get_next_line.git
cd get_next_line

# Compile with custom BUFFER_SIZE (mandatory part)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c -o gnl_test

# Compile with bonus (multiple file descriptors)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c your_main.c -o gnl_bonus
```

The `BUFFER_SIZE` can be any positive integer.

---

## 🚀 Usage

### Including in Your Project

1. **Copy files to your project:**
```bash
cp get_next_line.c get_next_line_utils.c get_next_line.h your_project/
```

2. **Include the header:**
```c
#include "get_next_line.h"
```

3. **Compile with BUFFER_SIZE:**
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 your_file.c get_next_line.c get_next_line_utils.c -o your_program
```

### Example Programs

#### Basic File Reading

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     ret;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    while ((ret = get_next_line(fd, &line)) > 0)
    {
        printf("%s\n", line);
        free(line);
    }

    if (ret == -1)
        printf("Error reading file\n");
    else if (ret == 0)
        printf("End of file reached\n");

    close(fd);
    return (0);
}
```

#### Reading from stdin

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char    *line;
    int     ret;

    printf("Enter text (Ctrl+D to exit):\n");
    while ((ret = get_next_line(0, &line)) > 0)  // 0 = stdin
    {
        printf("You entered: %s\n", line);
        free(line);
    }

    return (0);
}
```

#### Multiple File Descriptors (Bonus)

```c
#include "bonus/get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1, fd2, fd3;
    char    *line;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);

    // Alternate reading between files
    get_next_line(fd1, &line);
    printf("File 1: %s\n", line);
    free(line);

    get_next_line(fd2, &line);
    printf("File 2: %s\n", line);
    free(line);

    get_next_line(fd1, &line);  // Back to file 1
    printf("File 1: %s\n", line);
    free(line);

    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
```

---

## 📖 Function Prototype

```c
int get_next_line(int fd, char **line);
```

### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fd` | `int` | File descriptor to read from (0-999 valid range) |
| `line` | `char **` | Address of pointer where the line will be stored |

### Return Values

| Value | Meaning | Description |
|-------|---------|-------------|
| `1` | Line read | A complete line has been read successfully |
| `0` | EOF reached | End of file (may still return last line) |
| `-1` | Error | Invalid fd, malloc failure, or read error |

### Important Notes

- Returns line **without** the `\n` character
- Caller **must free** the returned line
- Works with `fd` range: 0-999
- `BUFFER_SIZE` must be greater than 0

---

## 🔧 Implementation Details

### Static Variable Strategy

Your implementation uses a **single static variable** to preserve data:

#### Mandatory Version
```c
static char *array;  // Persists between calls
```

#### Bonus Version (Multiple FDs)
```c
static char *a[256];  // Array indexed by fd (supports up to 256 FDs)
```

### Core Algorithm

```c
int get_next_line(int fd, char **line)
{
    char        *buf;
    ssize_t     res;
    static char *array;  // or a[256] for bonus
    int         end;
    int         lel;

    // 1. Validation
    if (fd < 0 || fd > 999 || line == NULL || BUFFER_SIZE <= 0)
        return (-1);

    // 2. Allocate temporary buffer
    res = 1;
    buf = (char *)malloc(BUFFER_SIZE + 1);

    // 3. Read until newline found or EOF
    while (res > 0 && ft_strchr(array, '\n') == NULL)
    {
        res = read(fd, buf, BUFFER_SIZE);
        buf[res] = '\0';
        array = ft_strjoin(array, buf);  // Accumulate data
    }

    free(buf);

    // 4. Extract line up to newline
    end = ft_strlen(array, '\n');
    *line = ft_substr(array, 0, end);

    // 5. Save remainder for next call
    lel = ft_strlen(*line, 0);
    if (res != -1)
        array = ft_substr2(array, (end + 1), (ft_strlen(array, 0) - lel));

    // 6. Normalize return value
    if (res > 1)
        res = 1;

    return (res);
}
```

### Helper Functions

Your `get_next_line_utils.c` implements 5 custom functions:

#### 1. `ft_strlen()` - Dual-purpose length
```c
size_t ft_strlen(char *str, char c)
{
    int counter = 0;

    while (str[counter] != '\0')
    {
        if (str[counter] == c)
            return (counter);  // Return index of 'c'
        counter++;
    }
    return (counter);  // Or total length if 'c' not found
}
```
**Special feature:** Returns index of character `c` if found, otherwise returns total length.

#### 2. `ft_strchr()` - Find newline
```c
char *ft_strchr(const char *s, int c)
{
    int count = 0;

    if (!s)
        return (NULL);

    while (s[count])
    {
        if (s[count] == c)
            return ((char *)&s[count]);
        count++;
    }

    if (s[count] == '\0' && c == '\0')
        return ((char *)&s[count]);

    return (NULL);
}
```
**Purpose:** Check if `\n` exists in accumulated buffer.

#### 3. `ft_strjoin()` - Concatenate and free
```c
char *ft_strjoin(char *s1, char *s2)
{
    char    *array;
    size_t  i;
    int     counter;

    if (!s1)
    {
        s1 = malloc(sizeof 1);
        s1[0] = '\0';
    }

    // Allocate new string
    array = malloc((ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1) * sizeof(char));
    if (!array)
        return (NULL);

    // Copy s1 then s2
    counter = 0;
    i = 0;
    while (i < ft_strlen(s1, 0))
        array[counter++] = s1[i++];

    i = 0;
    while (i < ft_strlen(s2, 0))
        array[counter++] = s2[i++];

    array[counter] = '\0';
    free(s1);  // Free old static buffer
    return (array);
}
```
**Key behavior:** Frees `s1` (old static buffer) automatically.

#### 4. `ft_substr()` - Extract substring
```c
char *ft_substr(char *s, unsigned int start, size_t len)
{
    char            *array;
    unsigned char   *src;
    size_t          dstcount;

    src = (unsigned char *)s;
    dstcount = 0;

    if (!src)
        return (NULL);

    array = malloc((len + 1) * sizeof(char));
    if (!array)
        return (NULL);

    if (start >= ft_strlen(s, 0))
    {
        array[0] = '\0';
        return (array);
    }

    while (dstcount < len)
        array[dstcount++] = src[start++];

    array[dstcount] = '\0';
    return (array);
}
```
**Purpose:** Extract the line (from 0 to newline position).

#### 5. `ft_substr2()` - Extract and free
```c
char *ft_substr2(char *s, unsigned int start, size_t len)
{
    // Same as ft_substr but...

    if (start >= ft_strlen(s, 0))
    {
        free(s);    // Free source
        free(array);
        return (NULL);
    }

    // ... copy substring ...

    free(s);  // Free old static buffer after extraction
    return (array);
}
```
**Key difference:** Frees `s` (old static buffer) after extracting remainder.

### Design Insights

#### Why Two substr Functions?

- **`ft_substr()`**: Used for extracting the **line** to return (doesn't free source)
- **`ft_substr2()`**: Used for extracting the **remainder** (frees old static buffer)

#### Memory Management Flow

```
Initial state:
  static array = NULL

After 1st read:
  static array = "Hello\nWorld"

Extract line:
  *line = ft_substr(array, 0, 5)  → "Hello"

Update static:
  array = ft_substr2(array, 6, 5)  → "World" (old array freed inside)

Next call:
  static array still has "World"
```

#### Bonus: Multiple File Descriptors

```c
static char *a[256];  // Array of 256 pointers

// Each fd has its own buffer
a[3] → "data from fd 3"
a[5] → "data from fd 5"
a[7] → "data from fd 7"
```

**Supports:** Up to 256 simultaneous file descriptors.

---

## 📁 Project Structure

```
get_next_line/
├── 📄 LICENSE                       # MIT License
├── 📄 get_next_line.h               # Header with prototypes
├── 📄 get_next_line.c               # Main implementation (static char *array)
├── 📄 get_next_line_utils.c         # 5 helper functions
├── 📄 gnlmain.c                     # Root test main
│
├── 📂 bonus/                        # Multiple FD support
│   ├── get_next_line_bonus.h
│   ├── get_next_line_bonus.c       # (static char *a[256])
│   └── get_next_line_utils_bonus.c
│
├── 📂 GNLmain/                      # Additional test files
│   ├── gnlmain.c
│   ├── main.c
│   └── test1.txt
│
├── 📂 mini/                         # Minimal test
│   └── prugnl.c
│
└── 📂 Tests/                        # External testers
    ├── 42tester-GNL/
    └── gnlTester/
```

### File Descriptions

| File | Lines | Purpose |
|------|-------|---------|
| `get_next_line.c` | ~50 | Main function with `static char *array` |
| `get_next_line_utils.c` | ~110 | 5 helper functions (strlen, strchr, strjoin, substr, substr2) |
| `get_next_line.h` | ~20 | Prototypes and BUFFER_SIZE inclusion |
| `*_bonus.c` | ~50 | Same as mandatory but with `static char *a[256]` |

### Compilation Notes

- **No Makefile** provided (intentional - project doesn't require it)
- Compile directly with `-D BUFFER_SIZE=value`
- No libft used (reimplemented necessary functions)

---

## 🧪 Testing

### Test with Different BUFFER_SIZES

```bash
# Minimum (stress test)
gcc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c gnlmain.c

# Small buffer
gcc -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c gnlmain.c

# Typical
gcc -D BUFFER_SIZE=4096 get_next_line.c get_next_line_utils.c gnlmain.c

# Large
gcc -D BUFFER_SIZE=1000000 get_next_line.c get_next_line_utils.c gnlmain.c
```

### Included Test Files

Your repository includes several test mains:

```bash
# Root level test
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c gnlmain.c -o test
./test GNLmain/test1.txt

# GNLmain directory tests
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c GNLmain/main.c -o test
./test

# Minimal test
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c mini/prugnl.c -o test
./test
```

### Edge Cases to Test

- **Empty file**: No content
- **Single line no newline**: `"Hello"` (no `\n` at end)
- **Only newlines**: File with just `\n\n\n`
- **Very long lines**: Lines exceeding BUFFER_SIZE multiple times
- **BUFFER_SIZE = 1**: Most challenging (1 char at a time)
- **Invalid FD**: `-1`, `1000`, closed descriptor
- **Multiple files (bonus)**: Alternating reads

### External Testers

Included in `Tests/` directory:

- **42tester-GNL** - Comprehensive tests
- **gnlTester** - Edge case focused

```bash
cd Tests/gnlTester
make
```

### Manual Test Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     ret;
    int     count;

    fd = open("test.txt", O_RDONLY);
    count = 1;

    while ((ret = get_next_line(fd, &line)) > 0)
    {
        printf("Line %d: [%s]\n", count++, line);
        free(line);
    }

    printf("\nFinal return: %d\n", ret);
    close(fd);
    return (0);
}
```

---

## 💡 What I Learned

Through this project, I gained understanding of:

- ✅ **Static Variables**: Function-level persistent storage across calls
- ✅ **File Descriptors**: Working with `read()` system call and FD management
- ✅ **Buffer Management**: Accumulating data across multiple reads
- ✅ **Memory Management**: Strategic freeing inside helper functions
- ✅ **String Manipulation**: Building custom string functions without libft
- ✅ **Edge Case Handling**: EOF without newline, empty files, various BUFFER_SIZES
- ✅ **Multiple FD State**: Using static arrays indexed by file descriptor
- ✅ **Pointer to Pointer**: Understanding `char **line` parameter

### Key Challenges

1. **Memory Management Strategy**: Deciding when to free the static buffer (solved with `ft_strjoin` and `ft_substr2` freeing automatically)
2. **ft_strlen Dual Purpose**: Making it return index of character OR full length
3. **NULL Static Initialization**: Handling first call when static variable is NULL
4. **Remainder Calculation**: Computing correct indices for leftover data
5. **Return Value Logic**: Converting `read()` return to 1/0/-1 format
6. **Bonus Array Size**: Choosing 256 to support multiple FDs

### Design Decisions

**Why `ft_strjoin` frees s1?**
- Old static buffer no longer needed after concatenation
- Simplifies memory management in main function

**Why two substr functions?**
- `ft_substr`: Extract line (keep source intact)
- `ft_substr2`: Extract remainder (free source)

**Why `ft_strlen` takes a char parameter?**
- Dual purpose: find character index OR get full length
- Reduces number of helper functions needed

---

## 📏 Norm Compliance

This project follows the **42 Norm** (Norminette v3):
- ✅ Maximum 25 lines per function
- ✅ Maximum 5 functions per file
- ✅ Only `read`, `malloc`, `free` allowed
- ✅ No global variables (static variables allowed)
- ✅ No memory leaks
- ✅ No forbidden functions used

**Validation:**
- FD range: 0-999
- BUFFER_SIZE > 0
- NULL pointer checks

---

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details.

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

- **[libft](https://github.com/Z3n42/42_libft)** - Custom C library (not used in GNL per subject rules)
- **[ft_printf](https://github.com/Z3n42/ft_printf)** - Formatted output
- **[fdf](https://github.com/Z3n42/fdf)** - Uses GNL for parsing map files

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42)**

*42 Urduliz | Circle 1*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)

</div>
