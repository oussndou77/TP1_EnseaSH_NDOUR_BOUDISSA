# TP1_EnseaSH_NDOUR_BOUDISSA

## Introduction
This project is a micro-shell, named EnseaSH, designed to provide users with a simple yet functional command-line interface. It displays the exit codes and execution times of the executed commands. This README provides an overview of the features, compilation instructions, and examples of usage.

## Features

### 1. Display Welcome Message and Prompt
Upon launching, the shell displays a welcome message introducing users to the ENSEA Shell environment. A prompt (`enseash %`) is presented to accept user commands.

### 2. Execution of Simple Commands
Users can input and execute simple commands (commands without arguments). The shell then returns to the prompt for additional input.

### 3. Handling Shell Exit
The shell gracefully handles the "exit" command, allowing users to terminate the shell. Additionally, it responds to the end of input file (`<ctrl>+d`) by displaying a goodbye message.

### 4. Displaying Exit Code (or Signal) of the Previous Command
After executing each command, the shell displays the exit code or signal of the preceding command. This provides users with information about the success or failure of the executed command.

### 5. Measurement of Command Execution Time
The shell measures and displays the execution time of each command in milliseconds. This feature allows users to assess the performance of commands.

### 6. Execution of Complex Commands with Arguments
The shell supports the execution of complex commands with arguments. Users can input commands with multiple parameters, and the shell processes and executes them accordingly.

### 7. Handling Redirections to stdin and stdout with ‘<’ and ‘>’
EnseaSH supports input and output redirection using '<' and '>', enabling users to manage input/output streams for commands. This enhances the flexibility and functionality of the shell.

## Compilation and Execution
To compile and run EnseaSH, use the following commands:

```bash
gcc -o Question_i Question_i.c // i is the number of the Question
./EnseaSH


## Compilation and Execution
Enter simple or complex commands.
Use "exit" to exit the shell.
Use < and > to manage redirections.

## Examples of use
enseash % ls
[exit:0] % 
enseash % pwd
[exit:0] % 
enseash % date
[exit:0] % 
enseash % date
[exit:0] % ls -l
enseash % ls > filelist.txt
enseash [exit:0|1ms] % wc -l < filelist.txt
44
enseash [exit:0|4ms] % 

## Notes
Ensure proper error handling and resource management in your program. Feel free to continue enhancing and expanding features based on future needs.

Author: Adem BOUDISSA & Ousseynou NDOUR

Date: 12/08/2023
