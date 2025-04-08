/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:20:03 by ego               #+#    #+#             */
/*   Updated: 2025/04/07 19:37:23 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Redirects standard input and/or output.
 * 
 * @param fd_in Input file descriptor to be used as new STDIN.
 * @param fd_out Output file descriptor to be used as new STDOUT.
 * 
 * @return 1 on success, 0 if dup2 fails.
 */
int	redirect_io(int fd_in, int fd_out)
{
	if (fd_in != -1 && dup2(fd_in, STDIN_FILENO) == -1)
		return (0);
	if (fd_out != -1 && dup2(fd_out, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

/**
 * @brief Restores the standard input and output to the
 * standard input and output backups.
 * 
 * @param pipe Pointer to the pipeline structure.
 */
void	restore_standard_io(t_pipe *pipe)
{
	dup2(pipe->stdin_backup, STDIN_FILENO);
	dup2(pipe->stdout_backup, STDOUT_FILENO);
}
