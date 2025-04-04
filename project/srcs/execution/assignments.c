/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:00:58 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 15:09:41 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given string is an assignment (VAR=value).
 * It is an assignment if the string starts by a valid
 * identifier and there is an equal sign at some point.
 * 
 * @param arg The string to be checked.
 * 
 * @return 1 if it is an assignment, 0 otherwise.
 */
static int	is_assignment(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (arg[i] == '=');
}

/**
 * @brief Goes through the token list and skips all assignments
 * and redirections to get to the first command.
 * 
 * @param t Token list.
 * 
 * @return The first token that is not an assignment or a redirection.
 */
t_token	*skip_assignments(t_token *t)
{
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == TEXT && !is_assignment(t->str))
			return (t);
		if (t->type >= REDIRIN && t->type <= INDELI)
			t = t->nxt;
		t = t->nxt;
	}
	return (t);
}

/**
 * @brief Goes through the token list and does all
 * assignments until finding a command (valid or not).
 * 
 * @param t Token list.
 * @param vars Variables.
 * 
 * @return 1 on success, 0 if allocation fails.
 */
int	do_assignments(t_token *t, t_var *vars)
{
	int	assignment;

	assignment = 0;
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == TEXT)
		{
			assignment = is_assignment(t->str);
			if (assignment && !var_set_line(&vars, t->str))
				return (0);
			else if (!assignment)
				return (1);
		}
		if (t->type >= REDIRIN && t->type <= INDELI)
			t = t->nxt;
		t = t->nxt;
	}
	return (1);
}
