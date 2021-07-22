#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstddef>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// Function to Display the Prompt
void prompt()
{
    cout << "myshell:~$ ";
}

// SHELL Function which executes the codes
void shell(char *args[], int argn)
{
    char *command = args[0];
    bool inp = false;
    bool out = false;
    bool append = false;
    int pos;
    char input[100], output[100];
    pid_t process = fork();
    perror("execvp");

    if (process == 0)
    { // If the current process is the CHILD Process
        for (pos = 0; args[pos] != nullptr; pos++)
        {
            // Searching for STDIN
            if (strcmp(args[pos], "<") == 0)
            {
                args[pos] = NULL;
                strcpy(input, args[pos + 1]);
                inp = true;
            }

            // Searching for STDOUT
            if (strcmp(args[pos], ">") == 0)
            {
                args[pos] = NULL;
                strcpy(output, args[pos + 1]);
                out = true;
            }

            // Searching for APPEND ">>"
            if (strcmp(args[pos], ">>") == 0)
            {
                args[pos] = NULL;
                strcpy(output, args[pos + 1]);
                append = true;
            }
        }

        if (inp == true)
        {
            int newOutput = open(output, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
            dup2(newOutput, 1);
            close(newOutput);
            args[pos] = nullptr;
        }
        if (out == true)
        {
            int newInput = open(input, O_RDONLY);
            dup2(newInput, 0);
            close(newInput);
            args[pos] = nullptr;
        }
        if (append == true)
        {
            int newOutput = open(output, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
            dup2(newOutput, 1);
            close(newOutput);
            args[pos] = nullptr;
        }

        execvp(command, args);
        _exit(1);
    }

    else if (process < 0)
    {
        printf("fork() failed!\n"); // Failed Process if PID<0
        exit(1);
    }
    else
    {
        waitpid(process, nullptr, 0); // Wait for Parent
    }
}

// TYPE Function which determines if the input is part 1,2 or 4
void type(char *input)
{
    string commands;
    stringstream stream(input);
    vector<char *> arg;

    while (stream >> commands)
    { // Reading commands
        char *current = new char[commands.length() + 1];
        strcpy(current, commands.c_str()); // Converting to c_string
        arg.push_back(current);
    }

    char **args = new char *[arg.size() + 1]; // Array of charecter ponters to hold commands
    for (int pos = 0; pos < arg.size(); pos++)
    {
        args[pos] = arg[pos];
    }

    args[arg.size()] = nullptr;
    shell(args, arg.size()); // Calling the shell to execute the command
}

int main()
{
    while (1)
    {                       // Always Running
        size_t bufsize = 0; // Setting the buffer size to 0
        char *buffer;
        buffer = (char *)malloc(bufsize * sizeof(char));

        char *command = new char[1024];
        prompt();
        cin.getline(command, 1024); // Input from User

        if ((strcmp(command, "exit") == 0))
        {
            break; // If user enters exit, exit the code
        }

        char *token = strtok(command, ";"); // (Part 2): Tokenizing commands according to ";"

        while (token)
        {
            type(token);
            token = strtok(nullptr, ";");
        }
    }
    return 0;
}

// ANIRUDH UMARJI - (AMU180000)
