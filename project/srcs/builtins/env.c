/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:32:59 by ego               #+#    #+#             */
/*   Updated: 2025/03/13 18:37:19 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the env builtin: simply prints
 * the environment.
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments (should not be any).
 * 
 * @return Exit status.
 */
int	env_builtin(t_data *data, t_token *args)
{
	t_var	*v;

	if (args && args->type == TEXT)
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
