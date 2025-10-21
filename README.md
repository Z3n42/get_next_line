<div align="center">

# 📖 Get Next Line

### Reading a line from a fd is way too tedious

<p>
  <img src="https://img.shields.io/badge/Score-115%2F100-success?style=for-the-badge&logo=42" alt="42 Score"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Language"/>
  <img src="https://img.shields.io/github/license/Z3n42/get_next_line?style=for-the-badge" alt="License"/>
  <img src="https://img.shields.io/badge/42-Urduliz-000000?style=for-the-badge&logo=42&logoColor=white" alt="42 Urduliz"/>
</p>

*A function that reads and returns one line at a time from a file descriptor, introducing the concept of static variables in C.*

[Features](#-features) • [Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [Implementation](#-implementation-details) • [Testing](#-testing)

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [Function Prototype](#-function-prototype)
- [Implementation Details](#-implementation-details)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [What I Learned](#-what-i-learned)
- [Norm Compliance](#-norm-compliance)
- [License](#-license)

---

## 🎯 About the Project

**Get Next Line** is a project that challenges you to implement a function that reads a file line by line. Each call to `get_next_line()` returns the next line from a file descriptor, making it possible to read text files efficiently without loading the entire content into memory.

### Why Get Next Line?

This project introduces one of the most powerful concepts in C programming: **static variables**. Understanding how to maintain state across function calls is crucial for:
- **File I/O operations** - Reading large files efficiently
- **Persistent data** - Maintaining context between function calls
- **Buffer management** - Handling partial reads and leftovers
- **Memory optimization** - Reading only what's needed at each call
- **Multiple file descriptors** - Managing state for different sources simultaneously

The completed function becomes an essential tool for any C project that requires line-by-line file processing.

---

## ✨ Features

<table>
<tr>
<td width="50%">

### 📄 Line Reading
- Reads one line per call
- Handles files of any size
- Returns line without `\n` terminator
- EOF detection and handling
- Works with stdin and file redirection

</td>
<td width="50%">

### 🧠 Static Variables
- Preserves buffer between calls
- Single static variable (bonus)
- No global variables used
- Function-level scope persistence
- Clean memory management

</td>
</tr>
<tr>
<td width="50%">

### 🔧 Configurable Buffer
- Compile-time BUFFER_SIZE definition
- Works with BUFFER_SIZE from 1 to millions
- Efficient memory usage
- Optimized read operations
- Dynamic adaptation to buffer size

</td>
<td width="50%">

### 🎯 Multiple File Descriptors (Bonus)
- Simultaneous handling of multiple FDs
- Independent reading threads per FD
- No interference between descriptors
- Scalable to unlimited FDs
- Thread-safe state management

</td>
</tr>
</table>

---

## 🛠️ Installation

### Prerequisites

- **GCC** or **Clang** compiler
- **Make** (optional, for easier compilation)
- Unix-based system (Linux, macOS)

### Clone and Compile

```bash
# Clone the repository
git clone https://github.com/Z3n42/get_next_line.git
cd get_next_line

# Compile with custom BUFFER_SIZE (mandatory part)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Compile with bonus (multiple file descriptors)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus_test
```

The `BUFFER_SIZE` can be any positive integer (tested from 1 to 10,000,000).

---

## 🚀 Usage

### Including in Your Project

1. **Copy get_next_line files to your project:**
```bash
cp get_next_line.c get_next_line_utils.c get_next_line.h your_project/
```

2. **Include the header in your C files:**
```c
#include "get_next_line.h"
```

3. **Compile with your desired BUFFER_SIZE:**
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

#### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char    *line;
    int     ret;

    printf("Enter text (Ctrl+D to exit):\n");
    while ((ret = get_next_line(0, &line)) > 0)  // 0 is stdin
    {
        printf("You entered: %s\n", line);
        free(line);
    }

    return (0);
}
```

#### Multiple File Descriptors (Bonus)

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1, fd2, fd3;
    char    *line;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);

    // Alternate reading between different files
    get_next_line(fd1, &line);
    printf("File 1: %s\n", line);
    free(line);

    get_next_line(fd2, &line);
    printf("File 2: %s\n", line);
    free(line);

    get_next_line(fd1, &line);  // Back to file 1
    printf("File 1: %s\n", line);
    free(line);

    get_next_line(fd3, &line);
    printf("File 3: %s\n", line);
    free(line);

    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
```

---

## 📖 Function Prototype

### Mandatory Part

```c
int get_next_line(int fd, char **line);
```

### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fd` | `int` | File descriptor to read from (file, stdin, etc.) |
| `line` | `char **` | Address of pointer where the line will be stored |

### Return Values

| Value | Meaning | Description |
|-------|---------|-------------|
| `1` | Line read | A complete line has been read and stored in `line` |
| `0` | EOF reached | End of file has been reached (may still have a last line) |
| `-1` | Error | An error occurred (invalid fd, malloc failure, read error) |

### Important Notes

- The returned line **does not include** the `\n` character
- The caller **must free** the returned line
- Each call returns the **next line** in sequence
- Works with any valid file descriptor (files, stdin, pipes, etc.)

---

## 🔧 Implementation Details

### Static Variables Concept

Static variables maintain their value between function calls, making them perfect for preserving file reading state:

```c
int get_next_line(int fd, char **line)
{
    static char *buffer;  // Preserves leftover data between calls

    // buffer persists across multiple calls to get_next_line
    // allowing us to save unprocessed data for the next line
}
```

### Core Algorithm

1. **Check for leftover data** from previous call in static buffer
2. **Read from file descriptor** in chunks of BUFFER_SIZE
3. **Search for newline** character in accumulated data
4. **Extract line** up to newline (or EOF)
5. **Save remainder** in static buffer for next call
6. **Return appropriate status** (1, 0, or -1)

### Buffer Management Strategy

```c
// Pseudocode of the reading strategy
while (no newline found && not EOF)
{
    read(fd, buffer, BUFFER_SIZE);
    append buffer to accumulated data;
    check for newline in accumulated data;
}

extract line up to newline;
save remainder for next call;
return line;
```

### Multiple File Descriptors (Bonus)

For the bonus, the static variable becomes an array or linked list indexed by file descriptor:

```c
static char *buffers[OPEN_MAX];  // One buffer per possible FD

// Or using a linked list:
typedef struct s_fd_list
{
    int             fd;
    char            *buffer;
    struct s_fd_list *next;
}   t_fd_list;

static t_fd_list *fd_list;  // Single static variable managing all FDs
```

### Key Challenges Solved

1. **Partial line reads**: Handling lines longer than BUFFER_SIZE
2. **Leftover management**: Preserving unprocessed data between calls
3. **Memory efficiency**: Allocating only what's needed
4. **Edge cases**: Empty lines, no trailing newline, BUFFER_SIZE of 1
5. **Multiple FDs**: Maintaining independent state for each descriptor

---

## 📁 Project Structure

```
get_next_line/
├── 📄 get_next_line.h              # Header with prototypes and definitions
├── 📄 get_next_line.c              # Main GNL implementation
├── 📄 get_next_line_utils.c        # Helper functions (strlen, strjoin, etc.)
├── 📄 get_next_line_bonus.h        # Bonus header (multiple FDs)
├── 📄 get_next_line_bonus.c        # Bonus implementation
├── 📄 get_next_line_utils_bonus.c  # Bonus helper functions
└── 📄 README.md                    # This file
```

### File Descriptions

| File | Purpose |
|------|---------|
| `get_next_line.c` | Core function with static variable and reading logic |
| `get_next_line_utils.c` | Utility functions (no libft allowed) |
| `get_next_line.h` | Function prototypes, includes, and BUFFER_SIZE guard |
| `*_bonus.c/h` | Extended version handling multiple file descriptors |

---

## 🧪 Testing

### Test with Different BUFFER_SIZES

```bash
# Tiny buffer (stress test)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c

# Small buffer
gcc -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c main.c

# Medium buffer (typical)
gcc -D BUFFER_SIZE=4096 get_next_line.c get_next_line_utils.c main.c

# Large buffer
gcc -D BUFFER_SIZE=1000000 get_next_line.c get_next_line_utils.c main.c
```

### Edge Cases to Test

- **Empty file**: File with no content
- **Single line, no newline**: File ending without `\n`
- **Only newlines**: File with only `\n` characters
- **Very long lines**: Lines exceeding several BUFFER_SIZE
- **BUFFER_SIZE = 1**: Most challenging scenario
- **Invalid FD**: Negative or closed file descriptor
- **Multiple files**: Alternating reads between different FDs (bonus)
- **stdin with CTRL+D**: Terminal input handling

### Community Testers

- **[Francinette](https://github.com/xicodomingues/francinette)** - Comprehensive tester
- **[gnlTester](https://github.com/Tripouille/gnlTester)** - Specialized GNL tests
- **[gnl_lover](https://github.com/charMstr/GNL_lover)** - Edge case focused

### Manual Test Example

```c
// test.c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     ret;
    int     line_count;

    fd = open("test.txt", O_RDONLY);
    line_count = 1;

    while ((ret = get_next_line(fd, &line)) > 0)
    {
        printf("Line %d: [%s]\n", line_count++, line);
        free(line);
    }

    printf("\nReturn value: %d\n", ret);
    close(fd);
    return (0);
}
```

---

## 💡 What I Learned

Through this project, I gained deep understanding of:

- ✅ **Static Variables**: How they maintain state across function calls with function-level scope
- ✅ **File Descriptors**: Working with FDs for files, stdin, and other input sources
- ✅ **Buffer Management**: Efficiently handling partial reads and leftover data
- ✅ **Memory Management**: Dynamic allocation, careful freeing, and leak prevention
- ✅ **String Manipulation**: Building strings dynamically without standard library
- ✅ **Edge Case Handling**: EOF without newline, empty files, various BUFFER_SIZES
- ✅ **State Persistence**: Maintaining independent state for multiple file descriptors
- ✅ **Read System Call**: Low-level file I/O and understanding return values

### Key Challenges

1. **Understanding Static Variables**: Grasping how static variables persist between calls but remain local in scope
2. **Leftover Management**: Properly storing and retrieving unprocessed buffer data
3. **Dynamic Buffer Sizes**: Making the function work efficiently with any BUFFER_SIZE
4. **Multiple File Descriptors**: Managing state for multiple FDs without global variables (bonus)
5. **Memory Leak Prevention**: Ensuring all allocated memory is properly freed
6. **Edge Cases**: Handling unusual inputs like BUFFER_SIZE=1 or files without trailing newline

---

## 📏 Norm Compliance

This project strictly follows the **42 Norm** (Norminette v3):
- ✅ Maximum 25 lines per function
- ✅ Maximum 5 functions per file
- ✅ Only allowed functions: `read`, `malloc`, `free`
- ✅ No global variables (static variables allowed)
- ✅ No memory leaks
- ✅ No segmentation faults or undefined behavior

---

## 📄 License

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

This function complements other 42 projects:

- [libft](https://github.com/Z3n42/42_libft) - Custom C library (though not used in GNL)
- [ft_printf](https://github.com/Z3n42/ft_printf) - Formatted output function
- Future projects requiring file parsing and line-by-line processing

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42)**

*42 Urduliz | Circle 1*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)

</div>
