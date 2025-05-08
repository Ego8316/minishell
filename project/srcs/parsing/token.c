/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:17:50 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/08 18:31:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new str token node, making a duplicate of the given string.
 * 
 * @param str Token's string.
 * @param depth Token's depth.
 * 
 * @return The newly allocated node, NULL if allocation fails.
 */
t_token	*token_new_str(char *str, int depth)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->type = TEXT;
	new->depth = depth;
	new->wildcards = NULL;
	new->nxt = NULL;
	return (new);
}

t_bool	token_make(t_token_type type, char *str, int depth, int *wc, t_token **out)
{
	*out = malloc(sizeof(t_token));
	if (!*out)
	{
		if (str)
			free(str);
		return (FALSE);
	}
	(*out)->type = type;
	(*out)->str = str;
	(*out)->depth = depth;
	(*out)->nxt = 0;
	(*out)->wildcards = wc;
	return (TRUE);
}

/**
 * @brief Frees a token list node.
 * 
 * @param t Pointer to the node to be freed.
 * 
 * @return False.
 */
t_bool	token_free_node(t_token **t)
{
	if (*t && (*t)->str)
		free_str(&(*t)->str);
	if (*t && (*t)->wildcards)
		free((*t)->wildcards);
	if (*t)
		free(*t);
	return (FALSE);
}

t_bool	token_free_list(t_token **list)
{
	t_token	*token;

	token = *list;
	while (token)
	{
		*list = token->nxt;
		if (token->str)
			free(token->str);
		if (token->wildcards)
			free(token->wildcards);
		free(token);
		token = *list;
	}
	return (FALSE);
}

t_bool	token_add_last(t_token_type type, char *str, int depth, int *wc, t_token **list)
{
	t_token	*new;
	t_token	*loop;

	if (!token_make(type, str, depth, wc, &new))
		return (token_free_list(list));
	if (!*list)
	{
		*list = new;
		return (TRUE);
	}
	loop = *list;
	while (loop->nxt)
		loop = loop->nxt;
	loop->nxt = new;
	return (TRUE);
}
