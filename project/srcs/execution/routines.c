/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:58:29 by ego               #+#    #+#             */
/*   Updated: 2025/05/05 20:36:09 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets up the pipes for the current command in the pipeline.
 * 
 * Determines the correct file descriptors for each command based on its
 * position in the pipeline and uses `redirect_io` to perform the actual
 * redirections.
 * 
 * @param pipe Pointer to the pipeline structure.
 */
int	set_pipes(t_pipe *pipe, int i)
{
	if (i == 0)
		return (redirect_io(-1, pipe->pipes[1]));
	else if (i == pipe->n - 1)
		return (redirect_io(pipe->pipes[2 * i - 2], -1));
	else
		return (redirect_io(pipe->pipes[2 * i - 2], pipe->pipes[2 * i + 1]));
}

/**
 * @brief Waits for a process to terminate and retrieves its exit code.
 * 
 * Checks if the process was exited normally or was terminated by a signal and
 * returns the corresponding exit code. `wpid == pid` is a safeguard to ensure
 * the child process we just waited for actually is the one expected.
 * 
 * @param pid PID of the child process to wait for.
 * 
 * @return Exit code of the process.
 */
int	wait_and_get_exit_code(pid_t pid)
{
	int		status;
	pid_t	wpid;

	while (1)
	{
		wpid = waitpid(pid, &status, 0);
		if (wpid == -1 && errno == EINTR)
			continue ;
		break ;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

/**
 * @brief Executes a child process routine.
 * 
 * Sets up the pipes for the current command in the pipeline, closes unused
 * ends of the pipes, handles input and output redirections, and then
 * attempts to execute the command. Immediately returns 1 if a redirection
 * failed, and returns 0 if there actually is no command.
 * 
 * @param data Pointer to the main data structure.
 * @param cmd Command to execute in the child process.
 * @param i Index of the current command in the pipeline.
 * 
 * @return Exit code of the command, `M_ERR` if memory allocation fails.
 */
int	child_routine(t_data *data, t_cmd *cmd, int i)
{
	int		ret;

	set_pipes(data->pipe, i);
	close_pipes(data->pipe);
	if (!cmd->redir_in || !cmd->redir_out)
		return (1);
	if (!*cmd->argv)
		return (0);
	redirect_io(cmd->fd_in, cmd->fd_out);
	ret = execute_builtin(data, cmd->argv);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!ft_strchr(cmd->name, '/') && *data->pipe->paths)
		return (execute_system_bin(data->pipe, cmd));
	else
		return (execute_local_bin(data->pipe, cmd));
}

/**
 * @brief Waits for all child processes in the pipeline to finish and retrieves
 * their exit codes.
 * 
 * If an allocation fails in any child process, kills all remaining child
 * processes and returns `M_ERR`.
 * 
 * @param data Pointer to the main data structure.
 * 
 * @return Exit code of the last child process, `M_ERR` if allocation fails.
 */
int	parent_routine(t_data *data)
{
	int		i;
	int		exit_code;

	close_pipes(data->pipe);
	i = 0;
	exit_code = 0;
	while (i < data->pipe->n)
	{
		exit_code = wait_and_get_exit_code(data->pipe->pids[i]);
		if (exit_code == M_ERR)
		{
			kill_all_children(data->pipe);
			return (free_pipeline(data->pipe), M_ERR);
		}
		i++;
	}
	return (exit_code);
}
