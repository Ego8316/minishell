<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png" height="150" alt="42 Minishell Badge"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/42-Project-blue" height="32"/>
  <img src="https://img.shields.io/github/languages/code-size/Ego8316/minishell?color=5BCFFF" height="32"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Linux-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
  <img src="https://img.shields.io/badge/WSL-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
</p>

# Minishell

### 🎓 42 School – Final Grade: **125/100**

Tiny Bash-like shell written in C. Implements parsing, tokenization, variable expansion, heredocs, pipelines, and builtins while matching Bash behavior as closely as the subject requires.

---

## 📦 Features
- Lexer + parser building an AST with operator precedence (`&&`, `||`, pipes).
- Variable expansion (`$VAR`, `$?`), wildcard expansion (`*`), and quote handling.
- Heredoc support with Ctrl-C handling and temporary file cleanup.
- Pipelines with proper fd routing, redirections (`<`, `>`, `>>`, `<<`), and PATH lookup.
- Builtins: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.
- Prompt with user/host info, SHLVL management, and sensible error reporting.

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
- Supports pipelines (`cmd1 | cmd2`), logical operators (`cmd1 && cmd2`, `cmd1 || cmd2`), subshell-like grouping via precedence, and standard redirections.
- Environment and local variables handled via `export`, `unset`, and assignment prefixes (`VAR=value cmd`).
- Signals: Ctrl-C interrupts current input or heredoc; Ctrl-\ is ignored per subject.
- Exit codes mirror Bash for common errors (command not found, permission denied, etc.).

---

## 📄 License
MIT — see `LICENSE`.
