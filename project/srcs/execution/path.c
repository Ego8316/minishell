/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:36:09 by ego               #+#    #+#             */
/*   Updated: 2025/04/08 13:32:35 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the PATH environment variable and splits it to
 * get the different paths.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return Allocated array of paths, allocated empty
 * array if PATH is not set, NULL if allocation fails.
 */
char	**get_paths(t_data *data)
{
	t_var	*path;

	path = var_get(&data->vars, "PATH");
	if (!path)
		return (ft_split("", ':'));
	return (ft_split(path->value, ':'));
}

/**
 * @brief Gets the pathname for an extern command.
 * If none has been found, returns a duplicate of
 * the emptry string.
 * 
 * @param name Command name.
 * @param paths Paths to be searched.
 * 
 * @return Allocated pathname if found, allocated copy 
 * of the empty string if not, NULL if allocation fails.
 */
char	*get_pathname(char *name, char **paths)
{
	char	*pathname;

	while (*paths)
	{
		pathname = join_strs(*paths, "/", name);
		if (!pathname)
			return (NULL);
		if (!access(pathname, F_OK | X_OK))
			return (pathname);
		free_str(&pathname);
		paths++;
	}
	return (ft_strdup(""));
}
