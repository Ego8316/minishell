/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/11 13:34:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all there is to free in a NULL-terminated
 * array of strings and returns NULL.
 * 
 * @return NULL.
 */
static void	*free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	return (NULL);
}

/**
 * @brief Copies the envp variable and returns the
 * allocated copy.
 * 
 * @param envp Environment to be copied.
 * 
 * @return The allocated copy, NULL if allocation fails.
 */
static char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return ((char **)free_array(copy));
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/**
 * @brief Initializes the data structure.
 * 
 * @param data Pointer to the data structure.
 * @param envp Startup environment.
 * 
 * @return 0 if allocation fails, 1 otherwise.
 */
t_bool	data_init(t_data *data, char **envp)
{
	data->envp = copy_envp(envp);
	data->pwd = getcwd(0, 0);
	data->oldpwd = getenv("OLDPWD");
	if (!data->envp || !data->pwd || !data->oldpwd)
		return (0);
	return (1);
}
