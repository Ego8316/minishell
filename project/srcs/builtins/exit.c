/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:20 by ego               #+#    #+#             */
/*   Updated: 2025/04/01 18:50:49 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the argument is numeric. Skips the
 * leading spaces and a possible sign.
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
 * @brief Executes the exit builtin
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return 0 for success.
 */
int	exit_builtin(t_data *data, t_token *args)
{
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (!args || args->type != TEXT)
		clean_exit(data, g_last_exit_code);
	if (!is_numeric(args->str))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_exit(data, 2);
	}
	if (args->nxt && args->nxt->type == TEXT)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	clean_exit(data, ft_atoi(args->str));
	return (0);
}
