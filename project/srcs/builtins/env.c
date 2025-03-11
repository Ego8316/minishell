/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:32:59 by ego               #+#    #+#             */
/*   Updated: 2025/03/11 13:32:07 by ego              ###   ########.fr       */
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
int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args && args[0])
	{
		printf("env: Too many arguments.\n");
		return (1);
	}
	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	return (0);
}
