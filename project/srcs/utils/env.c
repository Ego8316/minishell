/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:22:07 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 16:50:10 by ego              ###   ########.fr       */
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

/**
 * @brief Goes through the environment variable and searches
 * for the value corresponding to the given key. Allocates
 * memory to give a copy of the value if found, empty string
 * otherwise.
 * 
 * @param data Pointer to the data structure.
 * @param key Key whose value is to be found.
 * 
 * @return Allocated copy of the value if found, allocated empty
 * string ("\0") otherwise. NULL if allocation fails.
 */
char	*get_value(t_data *data, char *key)
{
	int	len;
	int	i;

	len = ft_strlen(key);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(key, data->envp[i], len))
			return (ft_strdup(data->envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}
