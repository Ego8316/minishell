/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:40 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:42:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Searches for a variable in the list and removes the node with the
 * identifier that matches the argument. Does nothing if no match is found.
 * 
 * @param data Pointer to the main data structure.
 * @param arg The identifier of the variable to be removed.
 */
static void	unset_arg(t_data *data, char *arg)
{
	t_var	*v;
	t_var	*prev;
	t_var	*tmp;

	v = data->vars;
	prev = NULL;
	while (v)
	{
		if (!ft_strcmp(v->identifier, arg))
		{
			if (!prev)
				data->vars = v->nxt;
			else
				prev->nxt = v->nxt;
			tmp = v;
			v = v->nxt;
			free_str(&tmp->identifier);
			free_str(&tmp->value);
			free(tmp);
			return ;
		}
		prev = v;
		v = v->nxt;
	}
}

/**
 * @brief Executes the `unset` builtin: removes the specified environment
 * variable(s) from the environment and the variable list. Does nothing if the
 * variable cannot be found.
 * 
 * @param data Pointer to the main data structure.
 * @param args Arguments (list of identifiers to unset).
 * 
 * @return Exit status: 0 if the operation is successful (always).
 */
int	unset_builtin(t_data *data, char **argv)
{
	while (*argv)
	{
		unset_arg(data, *argv);
		argv++;
	}
	return (0);
}
