/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:32:59 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 15:24:39 by ego              ###   ########.fr       */
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
	int	i;

	if (args && args->type == TEXT)
		return (errmsg("env: too many arguments\n", 0, 0, 1));
	i = 0;
	while (data->envp[i])
		printf("%s\n", data->envp[i++]);
	return (0);
}
