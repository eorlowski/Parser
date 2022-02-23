# Ed's parser

C++ 

Compile with make, when under cygwin, possibly under POSIX too.
Whe compiling with mingw (mingw32-make), set USER_READLINE to false, because otherwise it will not comiple.
Unit tests (make test) does not work with mingw-make.

Description
-----------

Parses simple expressions, no whitespace, currently only supported operators: +, *, / and -.

Brackets supported too now! Escape with \ when on Unix command line.

When using Unix command line, escape * with \ if it is preceded with whitespace.

On windows command line, * cannot be preceded by whitespace.

Read from stdin: try echo "2 + 4 * (3 + 2)" | ./parser.exe

Added debug option: -d (if first argument, displays verbose debug information).

06-06-2020 Added interactive mode

Added unit testing and makefiles
--------------------------------

For building: go to src folder and execute make

For building unit tests: go to test folder and execute make

Run the test with ./testparser.exe or "make test" in the rootfolder.

You can use catch options like '-s'.


Known bugs
----------
Fixed: Expression of (3+4) is not handled correctly.

Fixed: In interactive mode, the arrow keys are not handled well.
Note: if compiled with the readline option, arrows will invoke history. To exclude readline library, set USE_READLINE variable in src/Makefile to false (or some other value than true).
