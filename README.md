# 🐚 minishell

A lightweight shell implementation written in C, inspired by bash. Developed as part of the 42 school curriculum.

**Authors:** aronnet & jcrochet

---

## About

Minishell is a simplified Unix shell that replicates core bash functionality. The project deepens understanding of processes, file descriptors, signal handling, and parsing — the building blocks of any command-line interpreter.

---

## Features

### Command Execution
- Execution of commands using `PATH` resolution or absolute/relative paths
- Support for command arguments and options
- Proper error handling for unknown commands

### Redirections
- Input redirection: `< file`
- Output redirection: `> file`
- Append redirection: `>> file`
- Here-document: `<< DELIMITER` with environment variable expansion inside heredoc content

### Pipes
- Pipeline support: `cmd1 | cmd2 | cmd3 ...`
- Unlimited chaining of pipes
- Proper file descriptor management across pipeline stages

### Environment Variables
- Variable expansion with `$VARIABLE`
- Exit status expansion with `$?`
- Proper handling of quotes and variable expansion rules

### Quoting
- Single quotes: preserve literal value of all characters
- Double quotes: preserve literal value except for `$` (variable expansion)
- Mixed and nested quote handling

### Signals
- `ctrl-C`: displays a new prompt on a new line
- `ctrl-D`: exits the shell
- `ctrl-\`: does nothing (in interactive mode)
- Proper signal handling in child processes and heredocs

### Built-in Commands
- `echo` with `-n` option
- `cd` with relative or absolute path
- `pwd` — print working directory
- `export` — set environment variables
- `unset` — remove environment variables
- `env` — display environment
- `exit` — exit the shell with optional status code

### Bonus Features
- **Logical operators:** `&&` and `||` with proper short-circuit evaluation
- **Wildcard expansion:** `*` pattern matching in the current directory

---

## Getting Started

### Prerequisites
- GCC or Clang compiler
- GNU Make
- GNU Readline library

### Installation

```bash
git clone <repository-url> minishell
cd minishell
make
```

### Usage

```bash
./minishell
```

You will be greeted with the minishell prompt:

```
minishell>
```

### Examples

```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> ls -la | grep minishell | wc -l
3

minishell> cat << EOF > output.txt
here_doc> Hello from heredoc
here_doc> $USER is here
here_doc> EOF

minishell> ls && echo "success" || echo "failure"
Makefile  minishell  src  include  libft
success

minishell> echo test*.c
test1.c test2.c test3.c

minishell> export MY_VAR="42 is the answer"
minishell> echo $MY_VAR
42 is the answer
```

---

## Architecture

```
minishell/
├── include/
│   └── minishell.h
├── libft/
├── src/
│   ├── builtins/
│   │   ├── echo.c                    # echo builtin
│   │   ├── for_env.c / for_env_2.c   # env builtin
│   │   ├── for_export.c              # export builtin
│   │   ├── ft_unset.c                # unset builtin
│   │   ├── fuction_for_cd.c / cd2.c  # cd builtin
│   │   ├── function_command_utils.c   # builtin helpers
│   │   └── other_command.c            # command dispatch
│   ├── execution/
│   │   ├── child.c / child2.c        # process creation & pipes
│   │   ├── choose_cmd.c / _2.c       # command type routing
│   │   ├── from_pipex.c / _2.c / _3.c # execve & PATH resolution
│   ├── main_utils/
│   │   ├── main.c                     # entry point & main loop
│   │   ├── main_utils1.c / 2.c       # helper functions
│   │   ├── exit.c / exit_utils.c / _2.c # exit handling
│   │   ├── verif_cmd.c / _2.c / _3.c # command verification & dispatch
│   ├── parsing/
│   │   ├── tokenizer.c               # lexical analysis
│   │   ├── tokenizer_utils.c / 2 / 3 / 4 # tokenizer helpers
│   │   ├── token_cmd.c / 2 / 2_2 / 3 # command structure building
│   │   ├── token_cmd_utils.c          # token helpers
│   │   ├── expand.c / expand_utils.c  # variable expansion ($VAR, $?)
│   │   ├── fill_all_tokens.c          # token population
│   │   ├── free_one_redirect.c        # redirect cleanup
│   │   └── syntax.c                   # syntax validation
│   ├── redirections/
│   │   ├── collect_heredoc.c          # heredoc input collection
│   │   ├── here_doc.c / _utils.c / _norm.c # heredoc management
│   │   ├── heredoc_expand.c           # $VAR expansion in heredocs
│   │   ├── in_match.c / _utils.c      # wildcard matching (bonus)
│   ├── signals/
│   │   ├── signal.c                   # interactive & parent signals
│   │   └── signal_2.c                 # child & heredoc signals
│   └── utils/
│       ├── clean_exit.c               # clean process exit
│       ├── split_modif.c              # custom split
│       ├── sturct_utils.c             # token/redirect constructors
│       └── utils.c / utils_2.c        # general helpers
└── Makefile
```

---

## Technical Highlights

- **Zero memory leaks** in the parent process (verified with Valgrind)
- Proper file descriptor management — no fd leaks at exit
- Robust signal handling across interactive mode, heredocs, and child processes
- Heredoc environment variable expansion while preserving delimiter integrity
- Readline integration with custom signal handlers

---

## Testing

Run with Valgrind to verify memory management:

```bash
valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all \
         --track-fds=yes ./minishell
```

For cleaner output (parent process only):

```bash
valgrind --child-silent-after-fork=yes --suppressions=supp.supp \
         --leak-check=full --track-fds=yes ./minishell
```
