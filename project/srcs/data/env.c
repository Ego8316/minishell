/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:22:07 by ego               #+#    #+#             */
/*   Updated: 2025/03/14 14:10:20 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_vars_size(t_var *vars)
{
	t_var	*v;
	int		size;

	size = 0;
	v = vars;
	while (v)
	{
		size++;
		v = v->nxt;
	}
	return (size);
}

/**
 * @brief Copies the environment variables from the var list.
 * 
 * @param envp Var list to be copied.
 * 
 * @return The allocated copy, NULL if allocation fails.
 */
char	**copy_envp(t_var *vars)
{
	char	**copy;
	int		i;
	t_var	*v;

	copy = (char **)malloc((get_vars_size(vars) + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	v = vars;
	while (v)
	{
		if (v->type == ENV)
		{
			copy[i] = join_strs(v->identifier, "=", v->value);
			if (!copy[i])
				return ((char **)free_array(copy));
			i++;
		}
		v = v->nxt;
	}
	copy[i] = NULL;
	return (copy);
}
