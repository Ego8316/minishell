/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:36:09 by ego               #+#    #+#             */
/*   Updated: 2025/04/01 16:49:11 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the PATH environment variable and splits it to
 * get the different paths. Exits the program if allocation fails.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return Allocated array of paths, NULL if PATH is not set.
 */
char	**get_paths(t_data *data)
{
	t_var	*path;
	char	**paths;

	path = var_get(&data->vars, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path->value, ':');
	if (!paths)
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	return (paths);
}
