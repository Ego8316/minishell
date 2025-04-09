/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 00:46:56 by ego               #+#    #+#             */
/*   Updated: 2025/04/10 01:27:55 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "fnmatch.h"

/**
 * @brief Given a path to a directory and a pattern,
 * 
 */
char	**get_matches(char *dirpath, const char *pattern)
{
	int				size;
	DIR				*dir;
	struct dirent	*entry;
	struct dirent	*tmp;
	char			*matches;

	dir = opendir(dirpath);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	tmp = entry;
	close(dir);
	return (matches);
}

/**
 * @brief Given a path to a directory and a pattern,
 * counts the number of matches.
 * 
 * @param dirpath Path to the directory to be searched.
 * @param pattern Pattern to be compared against.
 * 
 * @return Number of matches, -1 if an error occured.
 */
int	count_matches(char *dirpath, const char **pattern)
{
	int				count;
	DIR				*dir;
	struct dirent	*entry;

	count = 0;
	dir = opendir(dirpath);
	if (!dir)
		return (errmsg("minishell: opendir: ", strerror(dirpath), "\n", -1));
	entry = readdir(dir);
	while (entry)
	{
		if (fnmatch(entry->d_name, pattern, 0) == 0)
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

/**
 * @brief Checks if a string has a wildcard. For minishell,
 * we also check if there is no '/' in the string, as the
 * subject requires wildcards working only in the current
 * working directory.
 * 
 * @param s String to be checked.
 * 
 * @return 1 if the string has a wildcard and no '/', 0 otherwise.
 */
int	has_wildcard(char *s)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (s[i])
	{
		if (s[i] == '*')
			wd = 1;
		if (s[i] == '/')
			return (0);
		i++;
	}
	return (wd);
}

void	expand_wildcards(t_token *t)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*nxt;

	while (t)
	{
		if (t->type == TEXT && ft_char_in_str('*', t->str) != -1 && ft_char_in_str('/', t->str) == -1)
		{
			nxt = t->nxt;
		}
		t = t->nxt;
	}
}