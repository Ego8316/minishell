/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:12:00 by ego               #+#    #+#             */
/*   Updated: 2025/05/08 18:15:41 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the execution of built-in commands.
 * 
 * Checks if the first argument matches a known builtin and executes it.
 * Returns 127 if the command is not a builtin, and `M_ERR` on allocation
 * failure (e.g. export).
 * 
 * @param data Pointer to the main data structure.
 * @param argv Argument vector of the command.
 * 
 * @return Exit status of the builtin command, 127 if not a builtin, `M_ERR`
 * if memory allocation fails.
 */
int	execute_builtin(t_data *data, char **argv)
{
	if (!ft_strcmp(*argv, "cd"))
		return (cd_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "echo"))
		return (echo_builtin(argv + 1));
	if (!ft_strcmp(*argv, "env"))
		return (env_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "exit"))
		return (exit_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "export"))
		return (export_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "pwd"))
		return (pwd_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "unset"))
		return (unset_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, ".") || !ft_strcmp(*argv, "source"))
		return (errmsg("minishell: '.' (source) built-in not supported\n",
				0, 0, 1));
	return (CMD_NOT_FOUND);
}

/**
 * @brief Executes a command using a system binary found in the PATH.
 * 
 * Attempts to locate the binary for the command using PATH and executes it.
 * Returns 127 if the command is not found or PATH is empty or unset, `M_ERR` on
 * allocation failure or the result of `execve` if it fails.
 * 
 * @warning This function should only be called in a child process.
 * 
 * @param pipe Pointer to the pipeline structure.
 * @param cmd Command to be executed.
 * 
 * @return Exit code from `execve`, 127 if the command is not found, `M_ERR` if
 * memory allocation fails.
 */
int	execute_system_bin(t_pipe *pipe, t_cmd *cmd)
{
	cmd->pathname = get_pathname(cmd->name, pipe->paths);
	if (!cmd->pathname)
		return (M_ERR);
	if (!*cmd->pathname)
		return (errmsg_errnum(0, cmd->name, CMD_NOT_FOUND));
	if (execve(cmd->pathname, cmd->argv, pipe->envp) == -1)
		return (errmsg_errnum(0, "execve", errno));
	return (1);
}

/**
 * @brief Executes a command using a local binary.
 * 
 * Verifies that the command exists, is not a directory, and is executable,
 * if so executes it using `execve`. If not, prints the appropriate error
 * message.
 * 
 * @param pipe Pointer to the pipeline structure.
 * @param cmd Command to be executed.
 * 
 * @return Exit code from `execve`, or approriate error code.
 */
int	execute_local_bin(t_pipe *pipe, t_cmd *cmd)
{
	if (is_dir(cmd->name))
		return (errmsg_errnum(1, cmd->name, CMD_NOT_EXEC));
	if (access(cmd->name, F_OK) != 0)
		return (errmsg_errnum(1, cmd->name, errno));
	if (access(cmd->name, F_OK | X_OK) != 0)
		return (errmsg_errnum(1, cmd->name, errno));
	if (execve(cmd->name, cmd->argv, pipe->envp) == -1)
		return (errmsg_errnum(0, "execve", errno));
	return (1);
}

/**
 * @brief Executes a single command (not in a pipeline).
 * 
 * Handles variable assignments, redirections, and determines whether to
 * execute a builtin or binary (system or local).
 * 
 * @warning This function should not be called in a pipeline.
 * 
 * @param data Pointer to the main data structure.
 * @param t Token list starting at the command to execute.
 * @param cmd Command to execute.
 * 
 * @return Exit code of the command, `M_ERR` if allocation fails.
 */
static int	execute_command(t_data *data, t_token *t, t_cmd *cmd)
{
	int		ret;
	pid_t	pid;

	if (!*cmd->argv && !do_assignments(t, &data->vars))
		return (M_ERR);
	if (!cmd->redir_in || !cmd->redir_out)
		return (1);
	if (!*cmd->argv)
		return (0);
	redirect_io(cmd->fd_in, cmd->fd_out);
	ret = execute_builtin(data, cmd->argv);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strchr(cmd->name, '/') && *data->pipe->paths)
			ret = execute_system_bin(data->pipe, cmd);
		else
			ret = execute_local_bin(data->pipe, cmd);
		printf("child: ret = %i\n", ret);
		clean_exit(data, ret);
	}
	return (wait_and_get_exit_code(pid));
}

/**
 * @brief Executes a pipeline of commands.
 * 
 * Creates a pipeline structure and forks for each command in the pipeline.
 * If only one command is present, it uses the simplified `execute_command`.
 * 
 * @param data Pointer to the main data structure.
 * @param t Token list starting at the current execution block.
 * 
 * @return 1 if fork fails, `M_ERR` if memory allocation fails, exit code of
 * the last child otherwise.
 */
int	execute_pipeline(t_data *data, t_token *t)
{
	int	i;

	data->pipe = get_pipeline(data, t);
	if (!data->pipe && g_last_exit_code == HEREDOC_C)
		return (130);
	if (!data->pipe)
		return (M_ERR);
	if (data->pipe->n == 1)
		return (execute_command(data, t, data->pipe->cmds[0]));
	i = -1;
	while (++i < data->pipe->n)
	{
		data->pipe->pids[i] = fork();
		if (data->pipe->pids[i] == -1)
		{
			perror("minishell: fork");
			return (free_pipeline(data->pipe), 1);
		}
		else if (data->pipe->pids[i] == 0)
			clean_exit(data, child_routine(data, data->pipe->cmds[i], i));
		t = get_to_next_command(t);
	}
	return (parent_routine(data));
}
