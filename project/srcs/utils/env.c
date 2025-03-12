/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:22:07 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 16:28:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reallocates envp to add given line to it.
 * 
 * @param data Pointer to the data structure.
 * @param line Line to be added.
 * 
 * @return 0 on success, 1 if allocation fails.
 */
int	add_line(t_data *data, char *line)
{
	char	**envp;
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	envp = (char **)malloc((i + 2) * sizeof(char *));
	if (!envp)
		return (1);
	i = 0;
	while (data->envp[i])
	{
		envp[i] = data->envp[i];
		i++;
	}
	envp[i] = ft_strdup(line);
	if (!envp[i])
	{
		free(envp);
		return (1);
	}
	envp[i + 1] = 0;
	free(data->envp);
	data->envp = envp;
	return (0);
}
