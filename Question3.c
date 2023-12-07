#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFSIZE 1096



// Function to execute a simple command
void executeCommand(char* command) {
    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // This is the child process

        // Execute the command
        if (execlp(command, command, (char *)NULL) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[BUFSIZE];
    int inputChar;


    // Display the welcome message
    displayWelcomeMessage();

    while (1) {
        // Display the prompt
        write(STDOUT_FILENO, "enseash % ", 11);

        // Read the user input
        if (read(STDIN_FILENO, input, sizeof(input)) == -1) {
            perror("Error reading the command");
            exit(EXIT_FAILURE);
        }

        // Remove the newline character (if it exists)
        input[strcspn(input, "\n")] = '\0';

        // Read the user input character by character
        inputChar = getchar();

        // Check for Ctrl+d (EOF)
        if (inputChar == EOF) {
            write(STDOUT_FILENO, "Goodbye!\n", 9);
            break;
        }


        // Check if the user wants to exit
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO, "Goodbye!\n", 9);
            break;
        }

        // Execute the entered command
        executeCommand(input);
    }

    return 0;
}