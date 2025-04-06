/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:32:59 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 14:05:26 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the env builtin: simply prints
 * the environment.
 * 
 * @param data Pointer to the data structure.
 * @param argv Arguments (should not be any).
 * 
 * @return Exit status.
 */
int	env_builtin(t_data *data, char **argv)
{
	t_var	*v;

	if (*argv)
		return (errmsg("env: too many arguments\n", 0, 0, 1));
	v = data->vars;
	while (v)
	{
		if (v->type == ENV)
			printf("%s=%s\n", v->identifier, v->value);
		v = v->nxt;
	}
	return (0);
}
