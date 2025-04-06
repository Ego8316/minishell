/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:39:44 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 14:23:01 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Opens infile. If heredoc is present, infile actually
 * is the limiter. In that case, creates a temporary file and
 * calls get_heredoc to fill the file just like a regular one.
 * 
 * @param infile Name of the input file, or the limiter.
 * @param type Token type (either < or <<).
 * @param vars Variables (for heredoc).
 * 
 * @return File descriptor on success, -1 on failure and -2
 * if allocation fails.
 */
int	get_infile(char *infile, t_token_type type, t_cmd *cmd, t_var *vars)
{
	int		fd;

	if (type == REDIRIN)
		return (open(infile, O_RDONLY));
	else
	{
		cmd->heredoc_name = get_heredoc_name();
		if (!cmd->heredoc_name)
			return (-2);
		fd = open(cmd->heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!get_heredoc(infile, fd, vars))
		{
			close(fd);
			return (-2);
		}
		close(fd);
		return (open(cmd->heredoc_name, O_RDONLY));
	}
}

/**
 * @brief Opens the outfile either in truncation or appending mode depending
 * on the given token type and returns the file descriptor.
 * 
 * @param outfile Path to the output file.
 * @param type Token type (either > or >>).
 * 
 * @return File descriptor on success, -1 on failure.
 */
int	get_outfile(char *outfile, t_token_type type)
{
	if (type == REDIROUT)
		return (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else
		return (open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
}
