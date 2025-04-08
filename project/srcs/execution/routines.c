/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:58:29 by ego               #+#    #+#             */
/*   Updated: 2025/04/08 17:41:20 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets up the pipes.
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
 * @brief Given a process' pid, waits for its termination
 * (whether it exited or was ended by signal) and returns
 * its exit code.
 * 
 * @param pid Process' pid to be waited.
 * 
 * @return Process' exit code.
 */
int	wait_and_get_exit_code(pid_t pid)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(pid, &status, 0);
	if (wpid == pid && WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (wpid == pid && WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (wpid == pid)
		return (status);
	return (0);
}

/**
 * @brief Routine for a child process. First sets pipes, then closes
 * unused ends. After that, immediately returns 1 if there was an error
 * in redirections, immediately returns 0 if there actually is no command.
 * Then redirects standard input and/or output and tries and execute
 * the actual command.
 * 
 * @param data Pointer to the data structure.
 * @param cmd Child's command to execute.
 * @param i Child index.
 * 
 * @return Child's exit code, -2 if allocation fails.
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
 * @brief Waits for each child routine to end.
 * If an allocation fails, kills other children
 * and exits with exit code -2.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return Exit code of the last child, -2 if allocation fails.
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
