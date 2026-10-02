_This project has been created as part of the 42 curriculum by besaipid._

#get_next_line
##Description

get_next_line is a project from the 42 curriculum focused on file descriptors, dynamic memory allocation, static variables, and buffered input.

The goal of the project is to implement a function that reads and returns one line at a time from a file descriptor:
`
char	*get_next_line(int fd);
`

Each time get_next_line() is called, it returns the next available line from the given file descriptor. The function must work correctly regardless of the size of the file, the length of each line, or the value of BUFFER_SIZE.

A line includes the terminating \n character when one is present. If the final line of a file does not end with \n, it is returned without one.

The project also includes a bonus implementation that supports multiple file descriptors simultaneously. This means that calls to get_next_line() can be alternated between different files without losing the unread data belonging to each file descriptor.

Features

Reads a file descriptor one line at a time.

Works with different BUFFER_SIZE values.

Handles lines longer than BUFFER_SIZE.

Preserves unread data between function calls.

Returns the newline character when it is part of the line.

Correctly handles files whose final line has no newline.

Handles empty files.

Handles invalid file descriptors and read errors.

Uses dynamic memory allocation for returned lines.

Bonus version supports multiple file descriptors simultaneously.

Does not use lseek() to move backwards or forwards through the file.

###How get_next_line() works

The main idea is to separate the process into two parts:

Reading data

Extracting one complete line

The function uses a static variable to keep data that has already been read but does not belong to the current line.

For example, suppose a file contains:
`
Hello
World
42
`

and BUFFER_SIZE is 10.

The first read() may retrieve:

Hello\nWorl


The first call to get_next_line() returns:

Hello\n


The remaining data:

Worl


must be preserved for the next call.

The next read() continues from the current file position and may add:

d\n42\n


The saved data then becomes:

World\n42\n


The next call can therefore return:

World\n


This process continues until there is no more data.

Algorithm

The implementation uses a persistent buffer combined with repeated read() calls.

Step 1 — Check the file descriptor

Before reading, the function verifies that the file descriptor is valid and that reading from it is possible.

Invalid input or a failed read() results in NULL.

Step 2 — Read until a complete line exists

The function repeatedly calls:

read(fd, buffer, BUFFER_SIZE);


The newly read data is appended to the persistent storage.

Reading stops when one of the following happens:

A \n is found.

read() reaches the end of the file.

read() returns an error.

This allows the function to handle lines that are larger than BUFFER_SIZE.

Step 3 — Extract the next line

Once a newline is available, the function extracts everything from the beginning of the stored data through the \n.

For example:

Stored data:
Hello\nWorld\n


The returned line is:

Hello\n


The remaining data is:

World\n

Step 4 — Preserve the remaining data

The unread part is stored for the next call.

This is the key reason a static variable is used: its value survives after get_next_line() returns.

Step 5 — Return the allocated line

The extracted line is returned as a newly allocated, null-terminated string.

The caller is responsible for freeing it:

line = get_next_line(fd);
free(line);

#Why this algorithm?

A major requirement of the project is that get_next_line() must return exactly one line per call without losing data between calls.

A simple read() followed by returning the buffer would not be sufficient because one read() can contain:

less than one line,

exactly one line,

multiple lines,

or part of a very long line.

The persistent-buffer approach solves this problem by separating reading chunks of data from extracting logical lines.

Using a static variable is particularly appropriate because the unread part of the input needs to survive between calls without requiring the caller to manage that state.

The algorithm also avoids using lseek(). Instead, the file descriptor naturally keeps track of the current position, while the static storage keeps track of data that has already been read but not yet returned.

#Complexity

For a file containing n characters, the function reads each character from the file only as necessary, with read() processing data in chunks of BUFFER_SIZE.

The exact memory usage depends on the size of the current line and the amount of unread data that has already been read.

The returned line requires O(L) memory, where L is the length of that line.

#Bonus

The bonus version extends the mandatory implementation to support multiple file descriptors at the same time.

The main difference is that the saved data cannot be stored in a single static buffer.

For example:

`
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
get_next_line(fd2);
`

Each file descriptor needs to keep its own remaining data.

The bonus implementation therefore associates persistent storage with each file descriptor.

Conceptually:
`
fd 3 -> saved data for file 1
fd 4 -> saved data for file 2
fd 5 -> saved data for file 3
`

This allows calls to different file descriptors to be safely interleaved.

Bonus example

The following main() demonstrates alternating between two files:
`
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line;

	if (argc != 3)
	{
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		return (1);
	}

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		if (fd1 >= 0)
			close(fd1);
		if (fd2 >= 0)
			close(fd2);
		return (1);
	}

	while (1)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break;
		printf("FD1: %s", line);
		free(line);

		line = get_next_line(fd2);
		if (line == NULL)
			break;
		printf("FD2: %s", line);
		free(line);
	}

	close(fd1);
	close(fd2);
	return (0);
}
`

This program alternates between the two file descriptors and demonstrates that each one maintains its own reading state.

Files
File	Purpose
get_next_line.c	Mandatory implementation of get_next_line()
get_next_line.h	Mandatory function declaration and configuration
get_next_line_utils.c	String and memory helper functions
get_next_line_bonus.c	Bonus implementation supporting multiple file descriptors
get_next_line_bonus.h	Bonus function declaration and configuration
get_next_line_utils_bonus.c	Helper functions used by the bonus implementation
Compilation

There is no standalone executable or root-level Makefile required for this project.

The source files can be compiled together with a small test program.

Mandatory version

For example:
`
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	-I. example.c \
	get_next_line.c \
	get_next_line_utils.c \
	-o gnl
`

Then run:
`
./gnl path/to/file
`
Bonus version

Compile the bonus files instead:
`
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	-I. example_bonus.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \
	-o gnl_bonus
`

Run:
`
./gnl_bonus file1.txt file2.txt
`
Changing BUFFER_SIZE

BUFFER_SIZE can be specified at compile time:
`
-D BUFFER_SIZE=1

or:

-D BUFFER_SIZE=42


or:

-D BUFFER_SIZE=100000
`

The implementation is designed to work with different buffer sizes.

If BUFFER_SIZE is not provided during compilation, the header defines a default value of 1.

Usage

#A basic use of the function looks like this:
`
int		fd;
char	*line;

fd = open("file.txt", O_RDONLY);
if (fd < 0)
	return (1);

while ((line = get_next_line(fd)) != NULL)
{
	printf("%s", line);
	free(line);
}

close(fd);
`

The caller must free() every string returned by get_next_line().

The function returns NULL when there is no more data to read or when an error occurs.

Input examples
File with multiple lines

If the file contains:

Hello
World
42


successive calls return:

"Hello\n"
"World\n"
"42\n"

File without a final newline

If the file contains:

Hello
World
42


where 42 has no trailing \n, the final call returns:

"42"

Empty file

For an empty file:

get_next_line(fd);


returns:

NULL

Error handling

The implementation handles common invalid situations such as:

Invalid file descriptors.

Failed read() calls.

Empty files.

End-of-file conditions.

Lines larger than BUFFER_SIZE.

When there is no line left to return, get_next_line() returns NULL.

Resources

The following resources were useful for understanding the concepts required by this project:

read() — POSIX/Linux system call documentation.

open() — POSIX/Linux documentation for opening files.

close() — POSIX/Linux documentation for closing file descriptors.

C documentation for malloc() and free().

C documentation for static variables.

42 school project subject and evaluation requirements.

Useful documentation can be found through:

man 2 read

man 2 open

man 2 close

man 3 malloc

man 3 free

AI usage

AI was used as a learning and development support tool during the project.

It was used for:

Understanding concepts related to file descriptors and read().

Understanding how static variables work and why they are useful for preserving state between function calls.

Clarifying memory allocation and freeing.

Understanding how to handle data that spans multiple read() calls.

Finding and understanding possible errors in the implementation.

Reviewing the general structure and readability of the code.

Helping understand the requirements of the mandatory and bonus parts.

Improving the documentation and README structure.

AI was not used as a replacement for understanding the project. The implementation was studied, tested, and adapted as part of the learning process.

##42 Project

This project is part of the 42 curriculum and is designed to develop a better understanding of:

File descriptors.

System calls.

Static variables.

Dynamic memory allocation.

String manipulation.

Buffer management.

Error handling.

Managing persistent state.

Working with multiple file descriptors.

Writing modular C code.

The project provides practical experience with low-level input handling in C and demonstrates how higher-level operations such as "read one line" can be built using the lower-level read() system call.
