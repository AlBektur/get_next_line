*This project has been created as part of the 42 curriculum by besaipid.*

This repository contains **get_next_line**, a 42 school project by **besaipid**. The goal is to read a file descriptor one line at a time, regardless of how many `read()` calls are needed to reach the end of a line.

## What the function does

```c
char	*get_next_line(int fd);
```

Each call returns the next line from `fd` as a newly allocated, null-terminated string:

- A line ending in `\n` includes that newline.
- If the final line has no trailing newline, it is returned as-is.
- Once there is no more data to return, or if reading fails, the function returns `NULL`.
- The caller owns each returned string and must `free()` it.

The function keeps unread data between calls, so reading resumes where the previous call stopped. A line can be longer than `BUFFER_SIZE`; it is assembled over as many reads as necessary.

## Project requirements

- Read from the supplied file descriptor using `read()`.
- Return one line per call, including the newline character when present.
- Work with different positive `BUFFER_SIZE` values, including values defined at compile time.
- Use a static buffer to preserve data between calls; do not use `lseek()` to move around the input.
- The bonus implementation maintains independent saved data for multiple file descriptors, allowing calls to alternate between them.

## Files

| File | Purpose |
| --- | --- |
| `get_next_line.c` | Mandatory implementation |
| `get_next_line.h` | Mandatory public declaration and default `BUFFER_SIZE` |
| `get_next_line_utils.c` | String helpers used by the mandatory implementation |
| `get_next_line_bonus.c` | Bonus implementation for multiple file descriptors |
| `get_next_line_bonus.h` | Bonus public declaration and configuration |
| `get_next_line_utils_bonus.c` | String helpers used by the bonus implementation |

The headers define `BUFFER_SIZE` as `1` if it was not specified by the compiler. Override it with `-D BUFFER_SIZE=<positive number>` when building.

## Build and use

There is no standalone executable or root-level Makefile in this project. Compile the implementation together with a program that calls it. For example, save a small driver as `example.c`:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Build and run the mandatory implementation from the repository root:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  -I. example.c get_next_line.c get_next_line_utils.c -o gnl
./gnl path/to/file
```

To use the bonus version, include `get_next_line_bonus.h` and compile `get_next_line_bonus.c` and `get_next_line_utils_bonus.c` instead of the mandatory source files. For standard input, pass file descriptor `0` to `get_next_line`.

## Testing

The repository includes a tester in `gnl_tester/`. From the repository root, run:

```sh
make -C gnl_tester       # Run the available test suite
make -C gnl_tester m     # Mandatory tests
make -C gnl_tester b     # Bonus tests
```

The tester covers different buffer sizes, empty input, long lines, newline and no-final-newline cases, standard input, and alternating reads from multiple descriptors. On Linux, its memory checks use Valgrind when available.

## Author and AI-use disclosure

- **42 login:** `besaipid`
- **AI use:** AI was used to understand new concepts, find errors, and understand the project.
