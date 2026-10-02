<h1 align="center">🚀 Get_Next_Line</h1>
<p align="center">
  My second project in <strong>42 Common Core</strong> — let's goooooo (๑•̀ ᴗ•́)۷✧<br>
  A function that reads from a file descriptor, line by line, with dynamic memory management!
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/github/languages/top/HajerZam/C-Project-Get_Next_Line?style=flat-square" />
  <img src="https://img.shields.io/github/repo-size/HajerZam/C-Project-Get_Next_Line?style=flat-square" />
  <img src="https://img.shields.io/github/last-commit/HajerZam/C-Project-Get_Next_Line?style=flat-square" />
  <img src="https://img.shields.io/github/issues/HajerZam/C-Project-Get_Next_Line?style=flat-square" />
  <img src="https://img.shields.io/badge/42-Common%20Core-critical" />
  <img src="https://img.shields.io/badge/score-112-brightgreen?style=flat-square">
</p>

---

## 📊 Project Overview

| Metric                 | Details                             |
|------------------------|-------------------------------------|
| 📁 Project Name         | get_next_line                      |
| 🧠 Key Concepts         | File descriptors, buffers, dynamic memory |
| 🧩 Bonus Features       | Support for multiple FDs           |
| ⏱️ Time Spent           | ~2 weeks                           |
| 🔥 Difficulty           | Medium – High                      |

---

## 🎯 Goals

Build a robust version of:

```c
char *get_next_line(int fd);
````

That will:

* ✅ Read and return **one line at a time**
* ✅ Work with **any valid file descriptor**
* ✅ Handle **multiple FDs** (bonus)
* ✅ Use dynamic memory — no fixed-size line limits
* ✅ Preserve remaining buffer data between calls

---

## 📚 Core Concepts & Skills

### 🔧 File Descriptors & Low-Level I/O

* Work with `open`, `read`, `close`
* Understand `stdin`, `stdout`, `stderr`
* 🔗 [GeeksforGeeks - File Descriptors](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/)

### 🧵 Buffers & Persistent State

* Use a static buffer (stash) per FD to track leftover data
* Handle partial reads and newline detection

### 🧠 Dynamic Memory

* Use `malloc`, `free`, `strjoin`, `strdup` correctly
* Clean up to avoid memory leaks

### 🧰 String Utilities

Recreate or reuse:

* `strchr` → Find `\n`
* `strdup` → Duplicate memory
* `strjoin`, `substr` → Combine & extract string parts

---

## ⚙️ Project Flow (How it works)

```c
get_next_line(fd)
    ↓
[Read BUFFER_SIZE bytes]
    ↓
[Append to stash]
    ↓
[Search for newline '\n']
    ↓
[Extract line + update stash]
    ↓
Return line
```

| Step              | Description                        |
| ----------------- | ---------------------------------- |
| ✅ Validate input  | Check for valid fd and buffer size |
| 📥 Read from fd   | Until newline or EOF               |
| 💾 Save remainder | Static stash retains leftover data |
| 🧻 Extract line   | Up to and including `\n`           |
| 🔚 Handle EOF     | Return `NULL` when done            |

---

## 🔧 Helper Functions

| Function          | Purpose                               |
| ----------------- | ------------------------------------- |
| `ft_strchr`       | Locate `\n` in stash                  |
| `ft_strdup`       | Duplicate a string                    |
| `ft_strjoin_free` | Join stash and buffer, free old stash |
| `ft_substr`       | Extract a substring                   |

---

## 🧪 Example Execution

Input file:

```
Hello\nWorld\n42\n
```

| Call # | Returned Line | Stash After Call |
| ------ | ------------- | ---------------- |
| 1      | `Hello\n`     | `World\n42\n`    |
| 2      | `World\n`     | `42\n`           |
| 3      | `42\n`        | \`\` (empty)     |
| 4      | `NULL`        | EOF reached      |

---

## 🔄 Memory & Flowchart

```
[read(fd) → BUFFER] → [append to stash]
       ↓
[find newline] → [split stash]
       ↓
[return line] + [keep leftover in static stash]
```

> Tip: Use `valgrind` or `leaks` to verify no memory is left unfreed!

---

## 🔍 Bonus: Multiple FDs

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

get_next_line(fd1); // reads from file1
get_next_line(fd2); // independently reads from file2
```

Your implementation must track separate stash buffers for each FD.
Use something like a static array indexed by FD, or a custom linked list (if you're daring!).

---

## 📦 Resources

* [42 Project Docs](https://harm-smits.github.io/42docs/projects/get_next_line)
* [Repo: ayogun](https://github.com/ayogun/get_next_line)
* [Repo: nickdotht](https://github.com/nickdotht/get_next_line)
* [Medium: Deep Dive #1](https://medium.com/%40ayogun/master-file-i-o-operations-with-42s-get-next-line-project-5fb001d1fff5)
* [Medium: Deep Dive #2](https://medium.com/%40ahmed.ezzouine/1337-ft-get-next-line-file-i-o-7f55762e2445)
* [YouTube: Line by Line](https://www.youtube.com/watch?v=8E9siq7apUU)

---

## ✅ Checklist

* [x] Reads 1 line at a time (with `\n`)
* [x] Handles files of any size
* [x] Supports multiple FDs (bonus)
* [x] Uses only allowed functions
* [x] No memory leaks
* [x] Makefile with all required rules
* [x] Clean, modular code (helpers, no spaghetti!)

---

## Testing 

`get_next_line` simple main:
```c
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     i = 1;

    if (argc < 2)
        fd = 0; // stdin
    else
        fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);
    while ((line = get_next_line(fd)))
    {
        printf("[%d] %s", i++, line);
        free(line);
    }
    close(fd);
    return (0);
}
```

```bash
for n in 1 2 5 10 42 9999 10000000; do
  cc -Wall -Wextra -Werror -D BUFFER_SIZE=$n \
     get_next_line.c get_next_line_utils.c main.c -o gnl && ./gnl test.txt
done
```

> Master this project, and buffer logic will never scare you again 😤

---

<p align="center">
Made with 💻, ⚔️ and lots of malloc debugging.
</p>


---
