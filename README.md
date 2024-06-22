# Minishell

A custom implementation of a simple shell, inspired by bash, created as part of the 1337 school curriculum.

[Previous sections remain the same: Table of Contents, Overview, Features, Installation, Usage, Built-in Commands, Project Structure]

## Core Concepts

Understanding minishell involves grasping several key concepts in Unix-like systems and C programming. Here's an overview of the main concepts used in this project:

### 1. Process Management

- **Fork**: Used to create child processes for executing commands.
- **Exec family**: Functions like `execve()` replace the current process image with a new one to run commands.
- **Wait**: Functions like `wait()` and `waitpid()` allow the parent process to wait for child processes to finish.

### 2. File Descriptors and I/O Redirection

- File descriptors are used to handle input/output operations.
- Redirection involves changing the standard input (0), output (1), or error (2) streams.
- Implemented using system calls like `dup()`, `dup2()`, and `pipe()`.

### 3. Pipes

- Pipes allow communication between processes.
- Implemented using the `pipe()` system call, creating a unidirectional data channel.

### 4. Signal Handling

- Signals are software interrupts sent to a program to indicate events.
- Handled using functions like `signal()` or `sigaction()`.
- Common signals: SIGINT (Ctrl-C), SIGQUIT (Ctrl-\), SIGTERM.

### 5. Environment Variables

- Stored as strings in the form "name=value".
- Accessed and modified using functions like `getenv()`, `setenv()`, and `unsetenv()`.

### 6. Parsing and Lexical Analysis

- Involves breaking down the command line input into tokens.
- Handles quoting, escaping, and separating command arguments.

### 7. Memory Management

- Proper allocation and deallocation of memory using `malloc()`, `free()`, etc.
- Preventing memory leaks and segmentation faults.

### 8. Error Handling

- Proper checking of return values from system calls and functions.
- Setting and using the global variable `errno` for system call errors.

### 9. Builtin Commands

- Implemented within the shell code, not relying on external programs.
- Includes commands like cd, echo, pwd, export, unset, env, and exit.

### 10. External Command Execution

- Searching for executables in the PATH.
- Handling absolute and relative paths.


## Implementation Details

Here are some specific details about how these concepts are implemented in our minishell:

1. **Command Parsing**: We use a custom parser that tokenizes the input string, handling quotes and escape characters.

2. **Execution Flow**: 
   - Parse input
   - Handle built-ins internally
   - For external commands, fork a child process
   - In the child, set up any necessary pipes or redirections, then use execve
   - Parent waits for child to complete

3. **Redirection**: We use dup2 to replace standard file descriptors with the appropriate files or pipes.

4. **Signal Handling**: We set up custom signal handlers for SIGINT and SIGQUIT to mimic bash behavior.

5. **Environment Management**: We maintain an internal copy of the environment, which we modify with our export and unset built-ins.

## Project Development Process

Here's an overview of how we approached and developed our minishell project:

1. **Project Planning and Research**
   - Thoroughly read the project requirements and bash manual
   - Researched UNIX processes, signals, and file descriptors
   - Outlined the main components of the shell

2. **Setting Up the Development Environment**
   - Created the project repository
   - Set up a Makefile for compilation
   - Established a basic project structure (directories for source files, headers, etc.)

3. **Implementing Basic Shell Loop**
   - Created a main loop to continuously prompt for and read user input
   - Implemented basic command execution for single commands without arguments

4. **Developing the Parser**
   - Designed and implemented a lexer to tokenize input
   - Created a parser to interpret the tokens and build a command structure

5. **Expanding Command Execution**
   - Implemented execution of commands with arguments
   - Added support for executing programs in PATH

6. **Implementing Built-in Commands**
   - Developed each built-in command (cd, echo, pwd, export, unset, env, exit)
   - Integrated built-ins into the main execution flow

7. **Adding Support for Pipes and Redirections**
   - Implemented input/output redirections (<, >, >>)
   - Added support for pipes (|) between commands

8. **Environment Variable Handling**
   - Created functions to manage environment variables
   - Implemented variable expansion in commands

9. **Signal Handling**
   - Added custom signal handlers for SIGINT, SIGQUIT, and SIGCHLD

10. **Quote Handling and Escape Characters**
    - Enhanced the parser to properly handle single quotes, double quotes, and escape characters

11. **Error Handling and Edge Cases**
    - Implemented comprehensive error checking
    - Handled various edge cases discovered during testing

12. **Memory Management**
    - Conducted thorough memory leak checks
    - Implemented proper memory allocation and deallocation throughout the project

13. **Testing and Debugging**
    - Developed a comprehensive test suite
    - Debugged issues uncovered during testing

14. **Code Refactoring and Optimization**
    - Refactored code for better readability and maintainability
    - Optimized performance where possible

15. **Documentation**
    - Wrote inline comments explaining complex parts of the code
    - Created this README to document the project

16. **Final Review and Submission**
    - Conducted a final code review
    - Ensured compliance with 42 School's norminette style guide
    - Submitted the project for evaluation

Throughout the development process, we adhered to best practices in C programming, followed the project guidelines closely, and regularly committed our changes to version control.
