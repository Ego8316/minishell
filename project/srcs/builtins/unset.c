/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:40 by ego               #+#    #+#             */
/*   Updated: 2025/03/14 17:24:41 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Goes through the var list to delete the node
 * with identifier identical to the argument given.
 * Does nothing if no such node can be found.
 * 
 * @param data Pointer to the data structure.
 * @param arg Supposedly the identifier.
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
 * @brief Executes the unset builtin: removes
 * the value for each found identifier. Does
 * nothing for unfound identifier. If the
 * identifier corresponds to an environment
 * variable, also removes it from envp.
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return 0 for success.
 */
int	unset_builtin(t_data *data, t_token *args)
{
	while (args && args->type == TEXT)
	{
		unset_arg(data, args->str);
		args = args->nxt;
	}
	return (0);
}
