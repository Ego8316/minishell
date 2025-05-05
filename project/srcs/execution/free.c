/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:23:42 by ego               #+#    #+#             */
/*   Updated: 2025/05/05 17:14:38 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all memory and resources associated with a command structure.
 * 
 * Closes file descriptors, unlinks heredoc file if necessary, frees all
 * strings, and finally frees the command structure itself.
 * 
 * @param cmd Command structure to be freed.
 * 
 * @return Always returns NULL for convenience in cleanup chains.
 */
void	*free_command(t_cmd *cmd)
{
	if (cmd)
	{
		free_array(cmd->argv);
		free_str(&cmd->name);
		free_str(&cmd->pathname);
		if (cmd->heredoc_name)
			unlink(cmd->heredoc_name);
		if (cmd->fd_in != -1 && cmd->redir_in)
			close(cmd->fd_in);
		if (cmd->fd_out != -1 && cmd->redir_out)
			close(cmd->fd_out);
		free_str(&cmd->heredoc_name);
		free(cmd);
	}
	return (NULL);
}

/**
 * @brief Frees an array of command structures.
 * 
 * Frees each command in the array and then frees the array itself.
 * 
 * @param cmds Array of command pointers.
 * @param n Number of commands in the array.
 * 
 * @return Always returns NULL for convenience in cleanup chains.
 */
void	*free_commands(t_cmd **cmds, int n)
{
	int	i;

	if (cmds)
	{
		i = 0;
		while (i < n)
		{
			free_command(cmds[i]);
			i++;
		}
		free(cmds);
	}
	return (NULL);
}

/**
 * @brief Sends SIGTERM to all child processes in the pipeline.
 * 
 * Iterates through the list of child PIDs and sends a termination signal
 * to each valid PID.
 * 
 * @param pipe Pointer to the pipeline structure.
 */
void	kill_all_children(t_pipe *pipe)
{
	int	i;

	if (!pipe || !pipe->pids)
		return ;
	i = 0;
	while (i < pipe->n)
	{
		if (pipe->pids[i] > 0)
			kill(pipe->pids[i], SIGTERM);
		i++;
	}
}

/**
 * @brief Frees all memory and resources associated with a pipeline structure.
 * 
 * Restores original standard input/output, frees memory used for the command
 * array, environment paths, file descriptors, and process IDs. Then frees
 * the pipeline structure itself.
 * 
 * @param pipe Pipeline structure to be freed.
 * 
 * @return Always returns NULL for convenience in cleanup chains.
 */
void	*free_pipeline(t_pipe *pipe)
{
	if (pipe)
	{
		restore_standard_io(pipe);
		free_array(pipe->paths);
		free_array(pipe->envp);
		if (pipe->pids)
			free(pipe->pids);
		if (pipe->pipes)
			free(pipe->pipes);
		free_commands(pipe->cmds, pipe->n);
		close(pipe->stdin_backup);
		close(pipe->stdout_backup);
		free(pipe);
	}
	return (NULL);
}
