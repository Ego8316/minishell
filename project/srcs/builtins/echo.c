/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:00 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 15:23:19 by ego              ###   ########.fr       */
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
	t_bool	n;

	n = FALSE;
	i = 0;
	if (arg[i++] != '-')
		return (n);
	while (arg[i] == 'n')
		i++;
	if (arg[i] == 0)
		n = TRUE;
	return (n);
}

/**
 * @brief Executes the echo builtin: prints all the given
 * strings and displays a newline depending on the -n option.
 * 
 * @param args Arguments.
 * 
 * @return 0 for success.
 */
int	echo_builtin(t_token *args)
{
	t_bool	nl;

	nl = TRUE;
	while (args && args->type == TEXT && is_n_option(args->str))
	{
		nl = FALSE;
		args = args->nxt;
	}
	while (args && args->type==TEXT)
	{
		printf("%s", args->str);
		if (args->nxt && args->nxt->type==TEXT)
			printf(" ");
		args = args->nxt;
	}
	if (nl)
		printf("\n");
	return (0);
}
