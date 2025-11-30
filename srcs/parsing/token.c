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
	new->nxt = NULL;
	new->prv = 0;
	new->wilds = 0;
	return (new);
}

/**
 * @brief Allocates and initializes a token node.
 *
 * Stores type, string pointer, depth, and resets links. Takes ownership of
 * the provided string pointer.
 *
 * @param type Token type to assign.
 * @param str String content (may be NULL).
 * @param depth Nesting depth.
 * @param out Output pointer for the allocated token.
 *
 * @return TRUE on success, FALSE on allocation failure (also frees `str`).
 */
t_bool	token_make(t_token_type type, char *str, int depth, t_token **out)
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
	(*out)->prv = 0;
	(*out)->wilds = 0;
	return (TRUE);
}

/**
 * @brief Frees a token list node.
 * 
 * @param t Pointer to the node to be freed.
 * 
 * @return False.
 */
t_bool	token_free_node(t_token *t)
{
	if (!t)
		return (FALSE);
	if (t->str)
		free_str(&t->str);
	if (t->wilds)
		free(t->wilds);
	free(t);
	return (FALSE);
}

/**
 * @brief Frees an entire token list.
 *
 * Iterates through the list freeing each node and its content.
 *
 * @param list Pointer to the head pointer of the list.
 *
 * @return FALSE (convenience for error paths).
 */
t_bool	token_free_list(t_token **list)
{
	t_token	*token;

	token = *list;
	while (token)
	{
		*list = token->nxt;
		token_free_node(token);
		token = *list;
	}
	return (FALSE);
}

/**
 * @brief Appends a token to the end of a token list.
 *
 * Updates previous/next pointers to preserve the doubly linked structure.
 *
 * @param token Node to append.
 * @param list Pointer to the head pointer of the list.
 *
 * @return TRUE on success, FALSE if `token` is NULL.
 */
t_bool	token_add_last(t_token *token, t_token **list)
{
	t_token	*loop;

	if (!*list || !token)
	{
		*list = token;
		return (TRUE);
	}
	loop = *list;
	while (loop->nxt)
		loop = loop->nxt;
	loop->nxt = token;
	token->prv = loop;
	return (TRUE);
}
