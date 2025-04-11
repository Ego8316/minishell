/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:22:07 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 02:18:53 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Computes the number of environment variables in the variable list.
 * 
 * @param vars Variable list.
 * 
 * @return The number of environment variables (elements with type `ENV`).
 */
static int	get_env_size(t_var *vars)
{
	t_var	*v;
	int		size;

	size = 0;
	v = vars;
	while (v)
	{
		if (v->type == ENV)
			size++;
		v = v->nxt;
	}
	return (size);
}

/**
 * @brief Copies the environment variables from the variable list into a new
 * array.
 * 
 * @param vars Variable list to copy the environment variables from.
 * 
 * @return A newly allocated array of environment variable strings in the
 * format `VAR=value`, NULL if memory allocation fails.
 */
char	**copy_envp(t_var *vars)
{
	char	**copy;
	int		i;
	t_var	*v;

	copy = (char **)malloc((get_env_size(vars) + 1) * sizeof(char *));
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
