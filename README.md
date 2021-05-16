<div align="center"><img src="protonlogo.png" width=300>

# proton
A programming language written entirely in C++.
(written in 4 hours in a challenge :yum:)

EN <u>[TR](README-TR.md)</u>
</div>

# License
[MIT License](LICENSE.md)

# Filetype
Default source file extension: ``.pfc``.

Default header file extension: ``.pfh``.

# Syntax

## Importing header files
You can import header files with **eat** keyword. nom nom

```c
eat "header.pfh"
```

## Variables
In this version of proton, all variables are global. So you can access and set them in everywhere. You can set them with **assign** keyword.

```c
assign a 5
```
proton can determine what type is this.

You can get the value of the variable just writing its name.
For example:

```c
assign a 5

write a
```

## Expressions

### IF
A classic if expression.

Examples:
```c
if 5 < 6 write "6 is bigger than 5"

if 90 > 6 write "90 is bigger than 6"

if "hi" is "hi" write "hi is equal to hi :D"

if "yes" not "no" write "yes is not no"
```

### Loops
In proton, there isn't a unique expression for loop (like for, while) but you can make a loop with **go** keyword.

Example 1 (1, 2, 3... is line numbers):

```c
1 meminit
2 assign a 1
3 write a
4 write end
5 assign a math sum a 1
6 go line 3
```

In line 6, the program goes to the third line and makes a loop goes forever.

(meminit: initializing base variables line end = end line = "\r\n")

Example 2:

```c
1  meminit
2  assign a 1
3  
4  write a
5  write end
6  assign a math sum a 1
7  if a not 5 go line 3
8  write "5"
9  write end
10 write "done."
```

## User Input / Output

### read
**read**: makes the user must enter a value to continue the program.

Example:
```c
assign a read

write "echo: "
write a
```

### write
**write**: writes a output to the STDIN.

Example:
```c
write "hello world."
```

## Points
A point is like a function but it's not. It isn't takes arguments. It's just a "point" to go.

(points can be in header files.)

Example:
```c
meminit

point test
    write "hi"
endpoint

go test

memdump
exit
```

Example 2 (with a header file):

header.pfh:
```c
meminit

point test
    write "Enter some text: "
    assign input read
    write "You entered: "
    write input
endpoint
```

source.pfc:
```c
eat "header.pfh"

go test
write end
write "done."

memdump
exit
```

## Other

### exit
exits the program with an exit code (if it's specified).

Example 1:
```c
write "hi"

exit
```

Example 2 (with a custom exit code):
```c
write "hi"

exit -1
```

### meminit
Initializes the memory with the base variables. like;

**end**: ``"\r\n"``

**back**: ``"\b"``

### memdump
Deletes all variables from memory.

### Convert
Converts a variable type to another.

```c
assign a "15"

convert int a
or
convert double a
```
(in proton main integer type is **double**)

## Contact
Discord: **fikret.#3849**

E-mail: fikretuwu@gmail.com
