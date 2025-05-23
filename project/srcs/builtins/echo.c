/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:00 by ego               #+#    #+#             */
/*   Updated: 2025/05/23 16:04:35 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if an argument corresponds to the `-n` option.
 * 
 * This function considers cases like `-nnnn`, which are supported in bash.
 * The argument is considered a valid `-n` option only when it consists
 * entirely of 'n' characters after the initial '-'.
 * 
 * @param arg Argument to be checked.
 * 
 * @return 1 if the argument is a valid `-n` option, 0 otherwise.
 */
static int	is_n_option(char *arg)
{
	int		i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

/**
 * @brief Executes the `echo` builtin command: prints the provided strings to
 * the standard output, and optionally suppressing the trailing newline if the
 * `-n` is present.
 * 
 * All arguments are printed with a space between them. The function then
 * prints a newline.The function checks if the first argument is a `-n` option,
 * and if so suppresses the newline at the end of the output. 
 * 
 * @param argv Array of strings, where the first argument may be a `-n` option.
 * 
 * @return Exit status: 0 if the operation is successful (always).
 */
int	echo_builtin(char **argv)
{
	int	nl;

	nl = 1;
	while (*argv && is_n_option(*argv))
	{
		nl = 0;
		argv++;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		if (*(argv + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		argv++;
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
