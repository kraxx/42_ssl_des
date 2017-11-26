# 42_libft
Recreation of Standard C Library for use in 42 Coding University's curriculum.
## Getting started
Run the following make command:
```
make
```
This will compile all the source files into a library file for use in the rest of your 42 curriculum projects.
To clean the folder of object files, run:
```
make clean
```
Running:
```
make fclean
```
will clean the library file itself as well.
This command:
```
make re
```
will first run make fclean, and then make.
## Background
42 Coding University encourages the creation of basic libc functions from the ground up, restricted to using only:
```
write
malloc
free
```
These basic files are compiled into our personal library "libft", to be used for the rest of the C curriculum at 42.
