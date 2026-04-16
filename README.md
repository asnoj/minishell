*This project has been created as part of the 42 curriculum by aronnet & jcrochet.*

<div align="center">

<h1>🐚 MINISHELL</h1>

**A lightweight Unix shell written in C — inspired by bash**

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42)](https://42lehavre.fr)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norm](https://img.shields.io/badge/Norm-v3-brightgreen?style=flat-square)](https://github.com/42School/norminette)

</div>

---

## 📖 Description

**minishell** is a 42 School project that reimplements a subset of the bash shell from scratch. It covers the full pipeline of a real shell: lexical analysis, parsing, expansion, execution, and signal handling — with a working interactive prompt powered by GNU Readline.

The project was built in pair programming and deepens understanding of processes, file descriptors, inter-process communication, and the POSIX signal API.

---

## ✨ Features

### Execution
- Command resolution via `PATH`, absolute, and relative paths
- Full argument and option support
- Proper exit code propagation (`$?`)

### Redirections
| Operator | Behavior |
|---|---|
| `< file` | Redirect stdin from file |
| `> file` | Redirect stdout to file (truncate) |
| `>> file` | Redirect stdout to file (append) |
| `<< DELIM` | Heredoc — read until delimiter, with `$VAR` expansion |

### Pipes
- Unlimited pipeline chaining: `cmd1 | cmd2 | cmd3 | ...`
- Correct file descriptor duplication and cleanup at each stage

### Quoting & Expansion
- Single quotes `'...'` — literal, no expansion
- Double quotes `"..."` — expansion of `$VAR` and `$?`
- Mixed and nested quote handling
- `$VARIABLE` and `$?` expansion in all contexts

### Built-in Commands
| Command | Description |
|---|---|
| `echo [-n]` | Print arguments, `-n` suppresses trailing newline |
| `cd [path]` | Change directory (relative or absolute) |
| `pwd` | Print current working directory |
| `export [VAR=value]` | Set or display environment variables |
| `unset VAR` | Remove an environment variable |
| `env` | Display all exported environment variables |
| `exit [code]` | Exit the shell with optional status code |

### Signals
| Signal | Interactive mode | Child process |
|---|---|---|
| `Ctrl-C` | New prompt on new line | Terminates child |
| `Ctrl-D` | Exits the shell | — |
| `Ctrl-\` | No effect | Terminates child |

### Bonus
- **Logical operators** — `&&` and `||` with correct short-circuit evaluation
- **Wildcard expansion** — `*` glob matching against the current directory

---

## 🚀 Usage

**Prerequisites:** `gcc`, `make`, GNU Readline (`libreadline-dev`)

```bash
git clone https://github.com/<your-username>/minishell.git
cd minishell
make
./minishell
```

```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> ls -la | grep ".c" | wc -l
42

minishell> cat << EOF > out.txt
heredoc> Hello $USER
heredoc> EOF

minishell> export MY_VAR="42 is the answer"
minishell> echo $MY_VAR
42 is the answer

minishell> ls *.c
main.c utils.c tokenizer.c

minishell> make && echo "ok" || echo "failed"
ok
```

---

## 🏗️ Architecture

```
minishell/
├── include/
│   └── minishell.h              # Global structs, enums, prototypes
├── libft/                       # 42 standard library
└── src/
    ├── builtins/                # echo, cd, pwd, export, unset, env, exit
    ├── execution/               # Process creation, pipes, execve, PATH resolution
    ├── main_utils/              # Main loop, prompt, command dispatch
    ├── parsing/
    │   ├── tokenizer.c          # Lexical analysis — splits input into tokens
    │   ├── token_cmd.c          # Builds command structures from token list
    │   ├── expand.c             # $VAR and $? expansion
    │   └── syntax.c             # Syntax validation before execution
    ├── redirections/
    │   ├── here_doc.c           # Heredoc collection and management
    │   ├── heredoc_expand.c     # Variable expansion inside heredocs
    │   └── in_match.c           # Wildcard pattern matching (bonus)
    ├── signals/
    │   ├── signal.c             # Interactive & parent process signal handlers
    │   └── signal_2.c           # Child process & heredoc signal handlers
    └── utils/                   # Memory cleanup, helpers, struct constructors
```

**Execution pipeline:**

```
Input string
     │
     ▼
[ Tokenizer ]  ──►  token list (WORD, PIPE, REDIR, OP...)
     │
     ▼
[ Parser ]     ──►  command list with redirections and args
     │
     ▼
[ Expander ]   ──►  $VAR / $? substitution, quote stripping
     │
     ▼
[ Executor ]   ──►  fork + execve / builtin dispatch / pipe setup
```

---

## 🧮 Technical Highlights

**Two-pass heredoc** — heredocs are collected before execution begins, so all `<<` delimiters are resolved upfront. This avoids race conditions between heredoc input and pipeline setup, and mirrors bash's actual behavior.

**Signal isolation** — signal handlers are swapped between three distinct states: interactive (parent waiting for input), heredoc collection, and child execution. Each state installs a different `sigaction` configuration to match the expected bash behavior precisely.

**No fd leaks** — every `dup2` is paired with a `close` and pipe ends are explicitly closed at each stage of the pipeline. File descriptor state is verified at shell exit with Valgrind's `--track-fds` option.

**Wildcard expansion without `glob()`** — the `*` matcher is implemented manually using `opendir`/`readdir`, building the match list from scratch without relying on any glob library.

---

## 🧪 Testing

```bash
# Memory leak check
valgrind ./minishell

# Norm check
norminette src/ include/
```

---

## 📚 Resources

- [bash manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [`fork` / `execve` — Linux manual](https://man7.org/linux/man-pages/man2/fork.2.html)
- [`sigaction` man page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [POSIX shell grammar](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

**AI usage:** AI was used exclusively for README writing and formatting. All source code was written manually without AI assistance, in compliance with the 42 AI policy for foundational projects.

---

<div align="center">

Made with ☕ at [42 Le Havre](https://42lehavre.fr) — **aronnet & jcrochet**

</div>
