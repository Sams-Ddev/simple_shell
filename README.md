# SIMPLE SHELL

![Simple shell Logo](https://velog.velcdn.com/images/leejaylight/post/7d11ca3b-f182-4724-a91f-bc39691b249c/%EA%B7%B8%EB%A6%BC1.png)

**Author:** Ashigbui Zerd  Samuel(Engineer_Zee)

**Project Start Date:** Oct 6, 2023 6:00 AM
**Project End Date:** Oct 19, 2023 6:00 AM

This project is a simple UNIX command interpreter implemented in C as part of the ALX Software Engineering program. It is a group project that challenges us to apply various concepts and skills related to programming, C, engineering mindset, group work, and learning strategies.

## PROJECT BACKGROUND
The Simple Shell project aims to create a basic command-line interpreter similar to the Unix shell. It is inspired by the concepts discussed in "The Gates of Shell" by Spencer Cheng, featuring Julien Barbier.

##CONCEPTS COVERED

- Basics of programming
- Basics of C programming
- Basics of thinking like an engineer
- Group work
- Learning how to learn

## IMPORTANT GUIDELINES

- All project work must be original, no copying of code from other sources or students is allowed.
- Coding should be done independently after understanding the concepts.
- Use of AI tools like ChatGPT is allowed within the context of learning.
- Focus on understanding and creating solutions rather than looking for shortcuts.
- Group projects involve mutual responsibility, and both partners must contribute and understand the code.
- Proper communication is necessary if unable to contribute to the project.
- Plagiarism is strictly forbidden and will result in removal from the program.

## LEARNING OBJECTIVES

By the end of this project, we are expected to be able to explain and demonstrate:

- General understanding of Unix operating system and shell concepts
- How to create a simple command interpreter in C
- How to use system calls like `execve`, `fork`, `wait`, `read`, etc.
- How to manipulate the environment of a process
- How to work with processes and their IDs (PID and PPID)
- How to handle built-in commands like `exit`, `env`, `cd`, etc.

## PROJECT STRUCTURE

- `main.c`: The main entry point of the shell.
- `shell.c`: Core logic of the shell implementation.
- `prompt.c`: Functions related to displaying the shell prompt.
- `exec.c`: Functions to handle command execution.
- `env-environ.c`: Handling environment variables.
- `cd.c`: Implementation of the built-in `cd` command.
- `helpers.c`: Helper functions used throughout the project.

## HOW  TO COMPILATION

To compile the shell, use the following command:

bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell


## HOW TO RUN AFTER COMPILATION

Run the shell in interactive mode:

bash
./simple_shell


Or execute commands from a file:

bash
./simple_shell commands.txt


## BUILT-IN COMMANDS

The shell supports the following built-in commands:

- `exit [status]`: Exit the shell with an optional status code.
- `env`: Print the current environment variables.
- `cd [DIRECTORY]`: Change the current working directory.
- `alias [name[='value']]`: Manage aliases for commands.
- `setenv VARIABLE VALUE`: Set a new environment variable.
- `unsetenv VARIABLE`: Remove an environment variable.

## How to generate AUTHORS file

Bash script for generating the list of authors in git repo

bash
#!/bin/sh

git shortlog -se \
  | perl -spe 's/^\s+\d+\s+//' \
  | sed -e '/^CommitSyncScript.*$/d' \
  > AUTHORS
<!-- The generates our AUTHORS file  for the repo -->

## Project Status

The project is in progress and will be completed by the specified deadline. We aim to meet all the learning objectives and provide a functional and efficient shell implementation.

Feel free to reach out to us if you have any questions or suggestions!

## Resources

- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
- [Everything you need to know to start coding your own shell concept page](https://intranet.alxswe.com/concepts/64)
- Other resources as provided by the course.

---

This project is a valuable opportunity for us to deepen our understanding of programming, C, and software engineering concepts. We are excited to learn, collaborate, and complete this project successfully!
