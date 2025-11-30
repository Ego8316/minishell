/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:39:44 by ego               #+#    #+#             */
/*   Updated: 2025/05/08 18:23:55 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes all pipe file descriptors in the pipeline.
 * 
 * Iterates through the pipe file descriptors and closes each one.
 * 
 * @param pipe Pointer to the pipeline structure.
 */
void	close_pipes(t_pipe *pipe)
{
	int	i;

	i = -1;
	while (++i < 2 * (pipe->n - 1))
		close(pipe->pipes[i]);
}

/**
 * @brief Opens an input file or handles a heredoc.
 * 
 * If the redirection type is '<', opens the given file for reading.
 * If it is '<<', treats `infile` as a limiter and generates a temporary
 * heredoc file using the limiter, then opens it for reading.
 * 
 * @param infile Input file name or heredoc limiter.
 * @param type Type of input redirection (`REDIRIN` or `INDELI`).
 * @param cmd Command structure (used to store heredoc filename).
 * @param data Pointer to the main data structure (used by heredoc).
 * 
 * @return File descriptor on success, -1 on failure, `M_ERR` if
 * memory allocation fails, `HEREDOC_C` if heredoc is Ctrl-C.
 */
int	get_infile(char *infile, t_token_type type, t_cmd *cmd, t_data *data)
{
	int		fd;

	if (type == REDIRIN)
		return (open(infile, O_RDONLY));
	else
	{
		cmd->heredoc_name = get_heredoc_name();
		if (!cmd->heredoc_name)
			return (M_ERR);
		fd = open(cmd->heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (get_heredoc(infile, fd, data) == HEREDOC_C)
		{
			close(fd);
			return (HEREDOC_C);
		}
		close(fd);
		return (open(cmd->heredoc_name, O_RDONLY));
	}
}

/**
 * @brief Opens an output file in either truncation or append mode.
 * 
 * Opens the given file according to the redirection type:
 * @brief - '>' (`REDIROUT`) truncates the file.
 * @brief - '>>' (`OUTAPPEND`) appends to the file.
 * 
 * @param outfile Output file name.
 * @param type Type of output redirection (`REDIROUT` or `OUTAPPEND`).
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

/**
 * @brief Checks if the given pathname points to a directory.
 * 
 * Uses `stat` to determine whether the given path is a directory.
 * 
 * @param pathname Pathname to be checked.
 * 
 * @return 1 if it is a directory, 0 otherwise.
 */
int	is_dir(char *pathname)
{
	struct stat	statbuf;

	ft_memset(&statbuf, 0, sizeof(struct stat));
	stat(pathname, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}
