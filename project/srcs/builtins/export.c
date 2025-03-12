/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:27 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 16:18:04 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Simply prints all exported variables in declare -x VAR="val" format.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return 0 for success.
 */
static int	print_declare_env(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp[i])
	{
		printf("declare -x ");
		j = 0;
		while (data->envp[i][j] != '=')
			j++;
		j++;
		printf("%.*s\"%s\"\n", j, data->envp[i], data->envp[i] + j);
		i++;
	}
	return (0);
}

/**
 * @brief Executes the export builtin: tries and put the given variable and its
 * value in the environment. If no argument given, prints all environment
 * variables with "declare -x " before.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return 0 on success, 1 otherwise.
 */
int	export_builtin(t_data *data, t_token *args)
{
	int	i;

	if (!args || args->type != TEXT)
		return (print_declare_env(data));
	i = 0;
	printf("%s", data->envp[i]);
	return (0);
}
