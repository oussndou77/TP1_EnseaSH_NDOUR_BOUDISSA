
#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1096

// Function to display the welcome message and prompt
void displayWelcomeMessage() {
    char message[BUFSIZE] = "Welcome to the ENSEA Shell.\nTo exit, type 'exit'.\nenseash %\n";
    write(STDOUT_FILENO, message, strlen(message));
}