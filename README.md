# Ed's parser

C++ Compile with for example: g++ -o parser.exe Parser.cpp

Description
-----------

Parses simple expressions, no whitespace, currently only supported operators: +, *, / and -.

Brackets supported too now! Escape with \ when on Unix command line.

When using Unix command line, escape * with \ if it is preceded with whitespace.

On windows command line, * cannot be preceded by whitespace.

Read from stdin: try echo "2 + 4 * (3 + 2)" | ./parser.exe

Added debug option: -d (if first argument, displays verbose debug information).

Added unit testing and makefiles
--------------------------------

For building: go to src folder and execute make

For building unit tests: go to test folder and execute make

Run the test with ./testparser.exe or "make test" in the rootfolder.

You can use catch options like '-s'.
