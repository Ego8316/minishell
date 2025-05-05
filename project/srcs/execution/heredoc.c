/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:01:59 by ego               #+#    #+#             */
/*   Updated: 2025/05/05 21:45:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a warning when heredoc is terminated by EOF rather than the
 * actual limiter.
 * 
 * Mimics the warning behavior of Bash when the user unexpectedly ends a
 * heredoc with Ctrl-D without providing the limiter.
 * 
 * @param limiter Expected limiter for the heredoc.
 * @param data Pointer to the main data structure.
 * 
 * @return Always returns 0 for convenience.
 */
static int	put_heredoc_warning(const char *limiter, t_data *data)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(data->line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(limiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	return (0);
}

/**
 * @brief Generates a unique filename for a temporary heredoc file.
 * 
 * The name is formed by appending a number to the fixed `TMP` prefix. It
 * increments a static counter with each call to ensure uniqueness.
 * 
 * @return Newly allocated string containing the unique filename, NULL if
 * memory allocation fails.
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
 * @brief Expand a variable found in a heredoc line and write its value to the
 * temporary file.
 * 
 * Handles both regular variables and '?'. Temporarily null-terminates the
 * string to isolate the variable identifier, retrieves its value for
 * the variable list and writes it to the heredoc temporary file if found.
 * The string is then restored to its original state.
 * 
 * @param line Line starting right after the $ sign.
 * @param fd File descriptor of the temporary file.
 * @param data Pointer to the main data structure.
 * 
 * @return Number of characters processed as the variable identifier.
 */
int	write_var_to_heredoc(char *line, int fd, t_data *data)
{
	int		i;
	char	tmp;
	t_var	*var;

	i = 0;
	if (line[i] == '?' && (!line[i + 1] || line[i + 1] == ' '))
	{
		ft_putnbr_fd(g_last_exit_code, fd);
		return (1);
	}
	while ((ft_isalnum(line[i]) || line[i] == '_')
		&& line[i] != ' ' && line[i] != '$')
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
 * @brief Writes the given line into the heredoc file, expanding variables.
 * 
 * Parses the line, replacing variables with their values.
 * 
 * @param line Line to be written with variable expansion.
 * @param fd File descriptor of the heredoc temporary file.
 * @param data Pointer to the main data structure.
 */
void	write_line_to_heredoc(char *line, int fd, t_data *data)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		while (line[i] == '$' && (line[i + 1] && line[i + 1] != ' '))
		{
			write(fd, line + j, i - j);
			i += write_var_to_heredoc(line + i + 1, fd, data) + 1;
			j = i;
		}
		i++;
	}
	ft_putendl_fd(line + j, fd);
}

// /**
//  * @brief Read user input lines into a heredoc until the limiter is reached.
//  * 
//  * Prompts the user line-by-line, expands variables within each line, and
//  * writes to a temporary file. Stops when the exact limiter string is entered,
//  * or when the user uses Ctrl-D.
//  * 
//  * @param limiter String that ends heredoc input.
//  * @param fd File descriptor of the heredoc temporary file.
//  * @param data Pointer to the main data structure.
//  * 
//  * @return 1 on success, `HEREDOC_C` if here-doc is Ctrl-C.
//  */
// int	get_heredoc(char *limiter, int fd, t_data *data)
// {
// 	pid_t	pid;
// 	char	*line;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		set_signals(2);
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if (!line)
// 				exit(put_heredoc_warning(limiter, data));
// 			if (!ft_strcmp(line, limiter))
// 				break ;
// 			write_line_to_heredoc(line, fd, data);
// 			free_str(&line);
// 		}
// 		free_str(&line);
// 		exit(0);
// 	}
// 	struct sigaction	sig;
// 	sig.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sig, NULL);
// 	return (wait_and_get_exit_code(pid));
// }


/**
 * @brief Read user input lines into a heredoc until the limiter is reached.
 * 
 * Prompts the user line-by-line, expands variables within each line, and
 * writes to a temporary file. Stops when the exact limiter string is entered,
 * or when the user uses Ctrl-D.
 * 
 * @param limiter String that ends heredoc input.
 * @param fd File descriptor of the heredoc temporary file.
 * @param data Pointer to the main data structure.
 * 
 * @return 1 on success, `HEREDOC_C` if here-doc is Ctrl-C.
 */
int	get_heredoc(char *limiter, int fd, t_data *data)
{
	char	*line;

	while (1)
	{
		// set_signals(1);
		line = readline("> ");
		// set_signals(0);
		if (g_last_exit_code == 130)
			return (HEREDOC_C);
		if (!line)
			return (put_heredoc_warning(limiter, data));
		if (!ft_strcmp(line, limiter))
			break ;
		write_line_to_heredoc(line, fd, data);
		free_str(&line);
	}
	free_str(&line);
	return (1);
}
