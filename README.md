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

[Remaining sections: Key Learnings, Future Improvements, Contributors, License]
