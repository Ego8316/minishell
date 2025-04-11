/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:32:59 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 02:40:21 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the `env` builtin: prints all the environment variables.
 * 
 * This function iterates over the linked list of environment variables stored
 * in the the main data structure. It prints each environment variable in the
 * format "VAR=value" to the standard output.
 * 
 * @warning As per the subject, does not handle any arguments.
 * 
 * @param data Pointer to the main data structure.
 * @param argv Arguments (should not be any).
 * 
 * @return Exit status: 0 if successful, 1 if any arguments are provided.
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
