/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:23:42 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 15:21:09 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all there is to free in a command
 * structure and returns NULL.
 * 
 * @param cmd Command structure to be freed.
 * 
 * @return NULL.
 */
void	*free_command(t_cmd *cmd)
{
	free_str(&cmd->name);
	free_str(&cmd->pathname);
	if (cmd->heredoc_name)
		unlink(cmd->heredoc_name);
	if (cmd->fd_in != -1 && cmd->redir_in)
		close(cmd->fd_in);
	if (cmd->fd_in != -1 && cmd->redir_out)
		close(cmd->fd_out);
	free_str(&cmd->heredoc_name);
	free_array(cmd->argv);
	free(cmd);
	return (NULL);
}

/**
 * @brief Frees all there is to free in a pipeline
 * structure and returns NULL.
 * 
 * @param pipe Pipeline structure to be freed.
 * 
 * @return NULL.
 */
void	*free_pipeline(t_pipe *pipe)
{
	free_array(pipe->paths);
	if (pipe->pids)
		free(pipe->pids);
	if (pipe->pipes)
		free(pipe->pipes);
	close(pipe->stdin_backup);
	close(pipe->stdout_backup);
	free(pipe);
	return (NULL);
}
