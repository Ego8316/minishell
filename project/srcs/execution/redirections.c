/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:20:03 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:40:32 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Redirects standard input and/or output.
 * 
 * Uses `dup2` to redirect standard input and/or standard output to the given
 * file descriptors. If either one of them is -1 (meaning not set), the
 * respective standard file descriptor is not redirected.
 * 
 * @param fd_in Input file descriptor to be used as new STDIN.
 * @param fd_out Output file descriptor to be used as new STDOUT.
 * 
 * @return 1 on success, 0 if `dup2` fails.
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
 * @brief Restores the standard input and output to the standard input and
 * output backups using `dup2`.
 * 
 * @param pipe Pointer to the pipeline structure.
 */
void	restore_standard_io(t_pipe *pipe)
{
	dup2(pipe->stdin_backup, STDIN_FILENO);
	dup2(pipe->stdout_backup, STDOUT_FILENO);
}

/**
 * @brief Processes an input redirection token.
 * 
 * Closes previously opened input file descriptor if opened. If previous one
 * is a heredoc, removes the corresponding temporary file and frees the
 * `heredoc_name` string as well. If `open` fails, prints the appropriate
 * error message.
 * 
 * @param cmd Current command being parsed.
 * @param t Token list.
 * @param data Pointer to the main data structure (for heredoc).
 * 
 * @return 1 on success, 0 on failure, `M_ERR` if allocation fails.
 */
int	get_input_redirection(t_cmd *cmd, t_token *t, t_data *data)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->heredoc_name)
	{
		unlink(cmd->heredoc_name);
		free_str(&cmd->heredoc_name);
	}
	cmd->fd_in = get_infile(t->nxt->str, t->type, cmd, data);
	if (cmd->fd_in == M_ERR)
		return (M_ERR);
	if (cmd->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(t->nxt->str);
		return (0);
	}
	return (1);
}

/**
 * @brief Processes an output redirection token.
 * 
 * Closes previously opened output file descriptor if opened. If `open` fails,
 * prints the appropriate error message.
 * 
 * @param cmd Current command being parsed.
 * @param t Output redirection token.
 * 
 * @return 1 on success, 0 on failure.
 */
int	get_output_redirection(t_cmd *cmd, t_token *t)
{
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	cmd->fd_out = get_outfile(t->nxt->str, t->type);
	if (cmd->fd_out == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(t->nxt->str);
		return (0);
	}
	return (1);
}
