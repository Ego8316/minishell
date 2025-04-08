/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:01:59 by ego               #+#    #+#             */
/*   Updated: 2025/04/08 19:26:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a bash warning similar to that of bash
 * when end-of-file is reached before finding the limiter
 * when filling a here-document.
 * 
 * @param limiter Here-doc limiter.
 * @param data Pointer to the data structure.
 * @param line Number of lines written during the here-doc.
 * 
 * @return 1.
 */
static int	put_heredoc_warning(const char *limiter, t_data *data, int line)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(data->line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(limiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	data->line += line;
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
 * @brief Gets the length of the variable identifier,
 * temporarily NULL-terminates the line to search for
 * a variable with this identifier and writes its value
 * if found.
 * 
 * @param line Line starting right after the $ sign.
 * @param fd File descriptor of the temporary file.
 * @param data Pointer to the data structure.
 * 
 * @return The length of the identifier.
 */
int	write_var_to_heredoc(char *line, int fd, t_data *data)
{
	int		i;
	char	tmp;
	t_var	*var;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	tmp = line[i];
	line[i] = 0;
	var = var_get(&data->vars, line);
	if (var)
		ft_putstr_fd(var->value, fd);
	line[i] = tmp;
	return (i);
}

/**
 * @brief Writes the given liven to the given file descriptor.
 * When encountering a $, expands the variable and writes its
 * value if and not empty, otherwise writes nothing.
 * 
 * @param line Complete line to be expanded and written.
 * @param fd File descriptor of the temporary file.
 * @param data Pointer to the data structure.
 */
void	write_line_to_heredoc(char *line, int fd, t_data *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			write(fd, line + j, i - j);
			i += write_var_to_heredoc(line + i + 1, fd, data) + 1;
			j = i;
		}
	}
	ft_putendl_fd(line + j, fd);
}

/**
 * @brief Copies user input to a temporary file until finding limiter.
 * Expands variables as well.
 * 
 * @param limiter Limiter.
 * @param fd File descriptor of the temporary file.
 * @param data Pointer to the data structure.
 * 
 * @return 1 on success, 0 on failure.
 */
int	get_heredoc(char *limiter, int fd, t_data *data)
{
	int		line_counter;
	char	*line;

	line_counter = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (put_heredoc_warning(limiter, data, line_counter));
		add_history(line);
		line_counter++;
		if (!ft_strcmp(line, limiter))
			break ;
		write_line_to_heredoc(line, fd, data);
		free_str(&line);
	}
	free_str(&line);
	data->line += line_counter;
	return (1);
}
