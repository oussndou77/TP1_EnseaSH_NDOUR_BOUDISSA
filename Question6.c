#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <bits/time.h>
#include <linux/time.h>

#define BUFSIZE 1096

void executeCommand(char* command) {
    struct timespec start, stop;
    double accum;

    // Record start time
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // This is the child process

        // Tokenize the command and its arguments
        char* args[BUFSIZE];
        char* token = strtok(command, " ");
        int i = 0;

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        // Execute the command with arguments
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);

        // Record end time
        if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("clock gettime");
            exit(EXIT_FAILURE);
        }

        // Calculate and display execution time
        accum = (stop.tv_sec - start.tv_sec) * 1000.0 + (double)(stop.tv_nsec - start.tv_nsec) / 1000000.0;

        // Convert the execution time to a string
        char timeStr[20]; // As 15 digits is enough for double
        int timeLen = snprintf(timeStr, sizeof(timeStr), "%.2lfms", accum);

        // Check if the process exited normally
        if (WIFEXITED(status)) {
            write(STDOUT_FILENO, "[exit:", 6);
            dprintf(STDOUT_FILENO, "%d", WEXITSTATUS(status));
            write(STDOUT_FILENO, "|", 1);
            write(STDOUT_FILENO, timeStr, timeLen);
            write(STDOUT_FILENO, "] % ", 4);
        } else if (WIFSIGNALED(status)) {
            // Check if the process was terminated by a signal
            write(STDOUT_FILENO, "[sign:", 6);
            dprintf(STDOUT_FILENO, "%d", WTERMSIG(status));
            write(STDOUT_FILENO, "|", 1);
            write(STDOUT_FILENO, timeStr, timeLen);
            write(STDOUT_FILENO, "] % ", 4);
        }
    }
}

int main() {
    char input[BUFSIZE];
    int inputChar;

    // Display the welcome message
    write(STDOUT_FILENO, "Welcome to the ENSEA Shell.\nTo exit, type 'exit'.\nenseash %\n", 62);

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
