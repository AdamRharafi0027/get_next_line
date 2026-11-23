*This project has been created as part of the 42 curriculum by **arharafi***

# get_next_line

## Description

> get_next_line is a project that help you dive into the file descriptors and the system calls functions.

the goal of this project is to iderstan how read system call reads data from a file discriptor and how it remember when he left read and how to manage  the memory from leaks;

## Instructions

### Usage

Include the header in your C source file:

```c
#include "get_next_line.h"
```
Use `get_next_line(fd)` in your program

```c
int main(void)
{
	char *line;
    line = get_next_line(fd);
	printf("%s", line);
	free(line);
    return (0);
}
```
<h3 style="color: #fc4b4b;">Don't Forget To "free(line)"</h3>


Compile your program with the files:

```bash
cc main.c get_next_line.c get_next_line_utils.c -o program
```

Run the program:

```bash
./program
```

## Project Structure

```text
get_next_line/
├─ get_next_line_utils.c
├─ get_next_line.c
├─ get_next_line.h
└─ README.md
```

- **get_next_line.c** :
	contains the main function

- **get_next_line_utils.c** :
	contains the helpers functions

- **get_next_line.h** :

	Contains function prototypes, and header guards, and BUFFER_SIZE macros

## Resources

- [Geeksforgeeks](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/)
- [Youtube](https://youtu.be/o9iZucYSkQA)


## AI Usage

I used AI tools to clarify C programming concepts, understand read(), learn how read() reads a file, and offsets, and file descriptors

<h2><sup>Logic of </sup> <span style="color: #00b5af;">`get_next_line`</span> <sub>that i use is : </sub></h2>

## VARIABLES :
- I use a one buffer taht will store the readed bytes by `read()` with `BUFFER_SIZE`
- I also use a two buffers one `reminder` with static type and another `tmp` for storing the new value was built from the concating of reminder and buffer.
- I also creat a `line` variable to save on it the line that i will return;
```
Why static :

using static for variables make the variables save or keep the previous value from the previous function call and it lifetime is depend by program life time not like normal variables that ends by the function lifetime
```
## FUNCTIONS:
### I create 5 functions do make the code easy and readable
<h4 style="color: #009e8c;">
	<code style="color: #009e8c;">char	*get_next_line(int fd)</code>
	 => MAIN FUNCTION
</h4>

get a file decriptor and return line by call on this file depend on the calls

<h4 style="color: #009e8c;">
	<code style="color: #009e8c;">int	fill_reminder(int fd, char **reminder)</code>
	 => HELPER FUNCTION
</h4>

this function get the `file descriptor` and the `dounble pointer to the reminder`
and returns an integer of how much bytes are written

and it takes double pointer cause we are changig on the original reminder

<h4 style="color: #009e8c;">
	<code style="color: #009e8c;">char	*get_remin(char *reminder)</code>
	 => HELPER FUNCTION
</h4>

this function gets `reminder` and return `the rest of the reminder`

EXAMPLE:
```c
reminder = "lo\nworld"
the get_remin() function return "world"
```

<h4 style="color: #009e8c;">
	<code style="color: #009e8c;">char	*get_line(char *reminder)</code>
	 => HELPER FUNCTION
</h4>

this function gets `reminder` and return `the lie that get_next_line will return`

EXAMPLE:
```c
reminder = "lo\nworld"
get_line() return "lo\n"
```

<h4 style="color: #009e8c;">
	<code style="color: #009e8c;">char	*free_reminder(char **reminder)</code>
	 => HELPER FUNCTION
</h4>
this function is for freeing the reminder and return `NULL`

<h3>The Core logic</h3>

- Read the <code>BUFFER_SIZE</code> and set it to the <code>buffer</code> then add a null terminator.

- And use <code>ft_strjoin</code> to cancatinate the reminder
and the buffer

- And then set the result in the <code>tmp</code> then free the reminder to receive the tmp then repeat that until we reach the <code>\n</code>


- If we reach the newline we extract the line from the reminder  using the get_line() function

- And then save it and save the reminder of that reminder that not containing the newline and etc.. until reach EOF (end of file)
That is 0 in the read()<sub>syscall<sub>

### And for the bonus :
	i just add a static struct with members fd and reminder and instead of sending the char *reminder we send node->reminder and free the node
	and concatenate the previous with the next of the removed to stay linked and a find node function that if is not exist created 


<h3 style="background: linear-gradient(to right, #8bffff, #00cdac); -webkit-background-clip: text; -webkit-text-fill-color: transparent; ">
    Created by Adam RHARAFI - 1337/42
</h3>
