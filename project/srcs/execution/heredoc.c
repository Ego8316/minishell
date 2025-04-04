/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:01:59 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 01:28:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a bash warning similar to that of bash
 * when end-of-file is reached before finding the limiter
 * when filling a here-document.
 * 
 * HERE PUT THE NUMBER OF COMMANDS INSTEAD OF 1
 * 
 * @param limiter Here-doc limiter.
 * 
 * @return 1.
 */
int	put_bash_warning(const char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(1, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(limiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	return (1);
}

/**
 * @brief Generates a unique name for a heredoc.
 * 
 * @return The new allocated heredoc name, NULL if allocation fails.
 */
char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(TMP, number);
	free(number);
	i++;
	return (name);
}

/**
 * @brief Copies user input to a temporary file until finding limiter.
 * Expands variables as well.
 * 
 * @param limiter Limiter.
 * @param fd File descriptor of the temporary file.
 * 
 * @return 1 on success, 0 on failure.
 */
int	get_heredoc(char *limiter, int fd, t_var *vars)
{
	int		eof;
	char	*line;

	eof = 0;
	line = NULL;
	while (!eof)
	{
		line = readline("> ");
		if (!line)
			eof = put_bash_warning(limiter);
		else if (!ft_strcmp(line, limiter))
			eof = 1;
		else
		{
			line = substitute_vars(line, vars);
			if (!line)
				return (0);
			ft_putendl_fd(line, fd);
		}
		free_str(&line);
	}
	return (1);
}
