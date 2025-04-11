/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:36:09 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:20:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the PATH variable and splits it to get the different paths.
 * 
 * Looks up the PATH variable in the variable environment. If found, it splits
 * the value into an array of individual paths using the colon as a delimiter.
 * If PATH is unset, returns an allocated empty array.
 * 
 * @param data Pointer to the main data structure.
 * 
 * @return Allocated array of paths (or empty if PATH is unset), NULL if memory
 * allocation fails.
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
 * @brief Gets the pathname for an external command.
 * 
 * Takes a command name and searches through the directories listed in the PATH
 * variable to locate the command's full pathname. If the command is found in
 * one of the directories, the full pathname is returned. If no match is found,
 * a duplicate of the empty string is returned.
 * 
 * @param name Command name to search for in PATH.
 * @param paths Array of directories to search.
 * 
 * @return Allocated pathname if found, allocated copy of the empty string if
 * not, NULL if allocation fails.
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
