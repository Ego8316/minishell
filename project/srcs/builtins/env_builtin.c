/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:32:59 by ego               #+#    #+#             */
/*   Updated: 2025/03/11 12:59:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all there is to free in a NULL-terminated
 * array of strings and returns NULL.
 * 
 * @return NULL.
 */
void	*free_array(char **arr)
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
char	**copy_envp(char **envp)
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
