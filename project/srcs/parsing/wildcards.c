/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 00:46:56 by ego               #+#    #+#             */
/*   Updated: 2025/05/23 17:09:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	record_wildcard(int i, int **wcs)
{
	int	*new;
	int	len;

	len = 0;
	while (*wcs && (*wcs)[len] != -1)
		len++;
	new = malloc((len + 2) * sizeof(int));
	if (!new)
	{
		if (*wcs)
			free(*wcs);
		return (FALSE);
	}
	new[len + 1] = -1;
	new[len] = i;
	while (len-- > 0)
		new[len] = (*wcs)[len];
	if (*wcs)
		free(*wcs);
	*wcs = new;
	return (TRUE);
}

/**
 * @brief Checks if the given filename is a match with the pattern contained in
 * the given token. Ensures hidden files are taken only if the pattern starts
 * with a dot. Also ensures directories . and .. do not appear in the matches.
 * 
 * @param filename Filename to check.
 * @param token Token node.
 * 
 * @return 1 if it is a match, 0 otherwise.
 */
static int	is_match(char *filename, t_token *t)
{
	if (ft_fnmatch(t->str, filename, 0, t->wilds))
		return (0);
	if (*filename == '.' && *t->str != '.')
		return (0);
	if (!ft_strcmp(filename, "."))
		return (0);
	if (!ft_strcmp(filename, ".."))
		return (0);
	return (1);
}

/**
 * @brief Builds up a token list made of all found matches for the given token.
 * If no match has been found, give only a copy of the given token node.
 * 
 * @param t Token node.
 * 
 * @return The matches list, NULL if allocation fails.
 */
t_token	*get_matches(t_token *t)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*matches;
	t_token			*head;

	matches = token_new_str(t->str, t->depth);
	if (!matches)
		return (NULL);
	head = matches;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (is_match(entry->d_name, t))
		{
			matches->nxt = token_new_str(entry->d_name, t->depth);
			if (!matches->nxt)
				return (closedir(dir), (t_token *)token_free_list(&head));
			matches = matches->nxt;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (head);
}

/**
 * @brief Inserts the matched files in the token list.
 * 
 * Cleans and sorts the matches filenames token list, frees the original
 * wildcard token, and updates the links in the token list accordingly.
 * 
 * @param h Pointer to the head of the token list.
 * @param p Pointer to the token preceding the current token.
 * @param m Pointer to the matches token list (wildcard expansion result).
 * @param t Pointer to the current token being replaced.
 * 
 * @return Pointer to the last token in the inserted matches list.
 */
static t_token	*add_wcs(t_token **h, t_token **p, t_token **m, t_token **t)
{
	t_token	*tail;

	tail = clean_matches(m);
	if (*p)
		(*p)->nxt = *m;
	else
		*h = *m;
	tail->nxt = (*t)->nxt;
	token_free_node(*t);
	return (tail);
}

/**
 * @brief Expands wildcard tokens within the token list.
 * 
 * Goes through the token list and expands tokens containing a wildcard and
 * no '/' by replacing them with the list of matching filenames in the current
 * directory. Matches are sorted lexicographically. Original wildcard tokens
 * are replaced and freed. Updates the head if needed.
 * 
 * @param head Pointer to the head of the token list (may be modified).
 * 
 * @return TRUE on success, FALSE if memory allocation fails.
 */
t_bool	expand_wildcards(t_token **head)
{
	t_token	*matches;
	t_token	*prev;
	t_token	*t;

	prev = 0;
	t = *head;
	while (t && t->type == TEXT)
	{
		if (!ft_strchr(t->str, '/') && ft_strchr(t->str, '*') && t->wilds)
		{
			matches = get_matches(t);
			if (!matches)
				return (FALSE);
			t = add_wcs(head, &prev, &matches, &t);
		}
		prev = t;
		t = t->nxt;
	}
	return (TRUE);
}
