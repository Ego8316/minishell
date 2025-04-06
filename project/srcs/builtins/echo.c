/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:00 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 14:04:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether an argument is the option -n.
 * Takes into account cases like -nnnnn that works in bash.
 * 
 * @param arg Argument to be checked.
 * 
 * @return True if the argument corresponds to the option -n,
 * false otherwise.
 */
static t_bool	is_n_option(char *arg)
{
	int		i;

	if (!arg || arg[0] != '-')
		return (FALSE);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

/**
 * @brief Executes the echo builtin: prints all the given
 * strings and displays a newline depending on the -n option.
 * 
 * @param argv Option and arguments.
 * 
 * @return 0 for success.
 */
int	echo_builtin(char **argv)
{
	t_bool	nl;

	nl = TRUE;
	while (*argv && is_n_option(*argv))
	{
		nl = FALSE;
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
