<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png" height="150" alt="42 minishell Badge"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/42-Project-blue" height="32"/>
  <img src="https://img.shields.io/github/languages/code-size/Ego8316/minishell?color=5BCFFF" height="32"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Linux-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
  <img src="https://img.shields.io/badge/WSL-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
</p>

# minishell

### 🎓 42 School – Final Grade: **125/100**

Tiny Bash-like shell written in C. Implements parsing, tokenization, variable expansion, heredocs, pipelines, and builtins while matching Bash behavior as closely as the subject requires.

---

## 📦 Features
- Lexer + parser building an AST with operator precedence (`&&`, `||`, pipes).
- Variable expansion (`$VAR`, `$?`), wildcard expansion (`*`), and quote handling.
- Heredoc support with Ctrl-C handling and temporary file cleanup.
- Standard redirections (`<`, `>`, `>>`, `<<`) across commands and pipelines.
- Pipelines with proper fd routing and PATH lookup.
- Logical operators (`cmd1 && cmd2`, `cmd1 || cmd2`) with precedence-aware
grouping.
- Builtins: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.
- Prompt with user/host info, SHLVL management, and sensible error reporting.
- Environment and local variables handled via `export`, `unset`, and assignment
prefixes (`VAR=value cmd`).
- Signals: Ctrl-C interrupts current input or heredoc; Ctrl-\ is ignored per
subject.
- Exit codes mirror Bash for common errors (command not found, permission
denied, etc.).

---

## 🛠️ Building
```bash
make          # build ./minishell
make clean    # remove object files
make fclean   # remove objects + binaries
make re       # rebuild from scratch
```
Requirements: `gcc`, `make`, and `readline` headers/libs (`libreadline-dev` on Debian/Ubuntu). Tested on Linux/WSL.

---

## 🚀 Usage
```bash
./minishell                 # interactive mode with prompt
./minishell -c "echo hi"    # run a single command and exit
echo "ls | wc -l" | ./minishell   # non-interactive stdin
```

---

## 🧩 Architecture Overview
Minishell follows a modular architecture:
- **Lexer** – tokenizes input into words, operators, and redirections.
- **Parser** – builds an AST respecting precedence rules (||, &&, |).
- **Expander** – performs `$VAR`, `$?`, and wildcard expansion.
- **Executor** – walks the AST and executes pipelines / commands.
- **Builtins** – implemented internally and executed without forking.
- **Signals** – custom handlers for interactive mode and heredocs.
- **Environment Manager** – linked-list environment with export sorting.

---

## ⚠️ Limitations (per subject)
- No subshells (`( )`)
- No job control (`fg`, `bg`, `jobs`)
- No globbing rules beyond simple `*` in the current directory

---

## 👥 Contributors
- [Ego8316](https://github.com/Ego8316)
- [petko021tv](https://github.com/petko021tv)

---

## 📄 License
MIT — see `LICENSE`.
