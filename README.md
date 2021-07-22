# AniShell

My Own custom Shell created using C++

1) Source Code Information
The source code is written in the C/C++ Language.
The code has only one file – code.cpp.
Here, first, the prompt myshell:-$ is displayed whose purpose is to tell the user that this is a shell.
The, the user can enter commands and see if they are working.

The code has 3 functions – 
•	Displays the prompt.
•	Parses the command to see what type it is.
•	Executes the Command.

The code has been well commented so that the person reading the code understands it.

2) Testing Information
Testing can be done using any linux system. 
The user should first check if the terminal has g++ installed in it.
This can be done using the code given below.

•	If g++ is not installed, use the command: sudo apt install build-essential
This command will install the necessary modules required by a linux system.

3) Running the Code
Use the command g++ code.cpp -o output.exe

The shell runs basic shell commands like: ls, echo, cat, mkdir, touch .etc.
