/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:20 by ego               #+#    #+#             */
/*   Updated: 2025/05/25 15:01:48 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the argument is numeric after skipping leading spaces and an
 * optional sign ('+' or '-').
 * 
 * @param arg Argument to be checked.
 * 
 * @return 1 if the argument is numeric, 0 otherwise.
 */
static int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	i += arg[i] == '+' || arg[i] == '-';
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Executes the `exit` builtin command: exits the program with provided
 * exit code.
 * 
 * Handles error cases like invalid arguments (non-numeric input) or too many
 * arguments. Prints an error message and exits if necessary.
 * 
 * @param data Pointer to the main data structure.
 * @param argv Arguments. The first argument is expected to be a numeric
 * string representing the exit code.
 * 
 * @return Exit status: 0 for success, 1 if too many arguments are provided,
 * 2 if the first argument is non-numeric.
 */
int	exit_builtin(t_data *data, char **argv)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!*argv)
		clean_exit(data, g_last_exit_code);
	if (!is_numeric(*argv))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_exit(data, 2);
	}
	if (*(argv + 1))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	clean_exit(data, ft_atoi(*argv));
	return (0);
}
