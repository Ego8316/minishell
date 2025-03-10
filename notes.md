# Environment variables

## Local and global variables
`A = hello` creates a **local shell variable**. It is only available in the current shell session.
`export A=hello` creates an **environment variable**. This is added to the environment, meaning child processes will inherit it.

## Behaviour
At minishell's startup, we should make a copy of `envp`. That copy should be the one used when using `execve` so commands inherit our modified environment, without touching that of the shell we used to start minishell.
Weird cases to take care of if we start minishell from minishell, but that should be fine.

## Related functions
`char *getenv(const char *name)` Searches the environment list to find the environment variable __name__, and returns a pointer to the corresponding __value__ string.
Can be used to get the initial working directory, but should not be used afterwards since we will be working with a copy of envp.

`char *getcwd(char *buf, int size)` When called with `buf = NULL` and `size = NULL`, allocates and returns a string corresponding to the current working directory.