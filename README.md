# 📚 **Get Next Line**

## 🚀 **Overview**
The **Get Next Line** project is a utility designed to read a single line of input from a file descriptor, even when the line spans multiple buffer reads. This function is particularly useful for handling large files or streams where lines may exceed a predefined buffer size.

## ✨ **Features**
- 📜 **Reads one line at a time** — Handles long lines split across multiple buffer reads.
- 📂 **File descriptor support** — Reads from files & standard input (`stdin`)
- ⚙️ **Customizable buffer size** — Adapts to any buffer size defined at compile time.
- 🔀 **Handles multiple file descriptors** — The *GNL* defined in bonus part files can read from multiple files or inputs simultaneously, maintaining separate buffers for each. It was implemented using a singly linked list, where each node stores the file descriptor and remaining content from the previous function call, allowing the function to manage and process multiple file descriptors independently without data interference. 📂🔗

---

## 🛠️ **Example Usage**
Function prototype: 
```
char *get_next_line(int fd);
```
To get the next line from a file or user input in C, you can use the following code:

```c
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int fd = open("file.txt", O_RDONLY);
	char *line = NULL;

	if (fd < 0)
    {
        perror("Error opening file");
		return (1);
    }

    // the loop fetches the next line until it  reaches EOF and prints it to stdin
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```
To get the next line from multiple file descriptors in C, you can use the following code:

```c
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1, fd2, fd3;
    char *line, *line1, *line2;

    // Open the file descriptors
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    
    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
        return (1);

    while (1)
    {
        line = get_next_line(fd1);
        line1 = get_next_line(fd2);
        line2 = get_next_line(fd3);
        
        // Break the loop when all file descriptors reach the end
        if (!line && !line1 && !line2)
            break;
    
        if (line)
        {
            printf("%s", line);
            free(line);
        }
        if (line1)
        {
            printf("%s", line1);
            free(line1);
        }
        if (line2)
        {
            printf("%s", line2);
            free(line2);
        }
    }
    close(fd1);
    close(fd2);
    close(fd3);

    return (0);
}
```
## ⚙️💻 Compilation 

To compile your program and use **get_next_line()**, follow these steps:

1. Ensure you have the required files and that the `get_next_line` function is implemented correctly.
2. Use the following `gcc` command to compile the program:

```bash
gcc -Wall -Wextra -Werror -o your_program your_source_file.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42
```
3. You don't need do import the BUFFER_SIZE macro, by default it's always 1.
4. To use **get_next_line()** for multiple file descriptors, compile the *bonus.c files instead.

## Error Handling ⚠️

The function includes several error-handling mechanisms to ensure programs that use it run smoothly. Here’s how errors are handled:

### 1. **File Opening Errors 📂❌**

- If an invalid file descriptor (e.g., -1) is passed, the function handles it implicitly.
- **File reading errors** are handled by checking the return value of the `read()` system call. If `read()` returns a negative value (indicating an error), the function frees any allocated memory and returns `NULL`.

```c
if (n_bytes < 0)
{
    free(content_storage);
    return (NULL);  // Error in reading from the file
}
```
### 2. Memory Allocation Failures 🛑

- **All `malloc` calls are followed by error checks** to ensure that if memory allocation fails, it is handled properly.
- **In case of failure**, any previously allocated memory is freed to avoid memory leaks.
- **`NULL` is returned** in the case of failure to signal that the function could not proceed due to insufficient memory.

This approach ensures that the program handles memory allocation failures gracefully, avoids leaks, and maintains stability even in the case of errors.


## 💬Notes
👀Feel free to submit a pull request if you want to contribute to this project!

📢 If you're a 42 student, use this as a guide at most. Don't cheat, learn! <3

📅 Created in December 2024 as part of 42's Common Core at 42 Warsaw

