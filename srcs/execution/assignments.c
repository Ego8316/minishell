/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:00:58 by ego               #+#    #+#             */
/*   Updated: 2025/05/01 23:42:04 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given string is a valid identifier. A valid identifier
 * must not be empty, must start with an alphabetic character or an underscore,
 * and must contain only alphanumeric characters or underscores.
 * 
 * @param arg The string to be checked.
 * 
 * @return 1 if the string is a valid identifier, 0 otherwise.
 */
int	is_valid_identifier(char *arg)
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
	return (1);
}

/**
 * @brief Checks if the given string is an assignment. An assignment starts
 * with a valid identifier followed by a '='.
 * 
 * @param arg The string to be checked.
 * 
 * @return 1 if the string is an assignment, 0 otherwise.
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
 * @brief Traverses the token list and skips all assignments and redirections
 * until the first command is encountered.
 * 
 * @param t Token list.
 * 
 * @return Pointer to the first token that is neither an assignment nor a
 * redirection.
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
 * @brief Processes all assignments in the token list until a command (valid or
 * not) is encountered. If the token represents an assignment, it is processed
 * and added to the variable list.
 * 
 * @param t Token list.
 * @param vars Variable list.
 * 
 * @return 1 on success, 0 if memory allocation fails.
 */
int	do_assignments(t_token *t, t_var **vars)
{
	int	assignment;

	assignment = 0;
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == TEXT)
		{
			assignment = is_assignment(t->str);
			if (assignment && !var_set_line(vars, t->str))
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
