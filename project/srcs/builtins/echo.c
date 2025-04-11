/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:00 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 01:19:54 by ego              ###   ########.fr       */
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
 * @brief Executes the `echo` builtin command, printing the provided strings
 * to standard output, and optionally suppressing the trailing newline if the
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
		printf("%s", *argv);
		if (*(argv + 1))
			printf(" ");
		argv++;
	}
	if (nl)
		printf("\n");
	return (0);
}
