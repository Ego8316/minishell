/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:46 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/22 20:13:42 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copies a quoted segment into the destination buffer, expanding vars.
 *
 * Reads until the matching quote is found. Within double quotes, expands
 * variables; within single quotes, copies literally.
 *
 * @param t Current token being expanded.
 * @param new Destination string builder.
 * @param i Index in the token string (advanced as characters are consumed).
 * @param v Variable list for substitutions.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
static t_bool	substitute_quote(t_token *t, char **new, int *i, t_var *v)
{
	char	q;

	q = t->str[(*i)++];
	while (t->str[*i] != q && t->str[*i])
	{
		if (q == '\"' && t->str[*i] == '$')
		{
			if (!substitute_var(t->str, i, v, new))
				return (FALSE);
		}
		else if (!strb_append(new, t->str[(*i)++]))
			return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Processes one step of variable and wildcard substitution.
 *
 * Handles quotes, variable expansion, wildcard position recording, and plain
 * character appends.
 *
 * @param t Current token being expanded.
 * @param vars Variable list.
 * @param i Index in the token string (advanced as characters are consumed).
 * @param new Destination string builder.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
static t_bool	substitute_loop(t_token *t, t_var *vars, int *i, char **new)
{
	if (t->str[*i] == '\'' || t->str[*i] == '\"')
	{
		if (!substitute_quote(t, new, i, vars))
			return (FALSE);
	}
	else if (t->str[*i] == '$')
	{
		if (!substitute_var(t->str, i, vars, new))
			return (FALSE);
	}
	else
	{
		if (!record_wildcard(*i, &t->wilds))
			return (FALSE);
		if (!strb_append(new, t->str[*i]))
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

/**
 * @brief Expands variables and records wildcards within a token string.
 *
 * Iterates over the token string, building a new version with substitutions.
 * Keeps `NULL` for empty results originating from quotes only.
 *
 * @param t Token to mutate.
 * @param vars Variable list.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
static t_bool	substitute_string(t_token *t, t_var *vars)
{
	int		i;
	char	*new;

	i = 0;
	new = 0;
	while (t->str[i])
		if (!substitute_loop(t, vars, &i, &new))
			return (FALSE);
	if (!new && (ft_strchr(t->str, '\"') || ft_strchr(t->str, '\'')))
		new = strb_new();
	free(t->str);
	t->str = new;
	return (TRUE);
}

/**
 * @brief Removes the current token from the list and frees it.
 *
 * Updates neighbor links to keep the list consistent.
 *
 * @param t Pointer to the current token pointer (updated to next).
 */
static void	delete_link(t_token **t)
{
	t_token	*del;

	del = *t;
	if (del->nxt)
		del->nxt->prv = del->prv;
	if (del->prv)
		del->prv->nxt = del->nxt;
	*t = del->nxt;
	token_free_node(del);
}

/**
 * @brief Performs variable substitution and wildcard expansion on a token list.
 *
 * Mutates tokens in place, removing empty text nodes and expanding wildcards
 * into multiple tokens when present.
 *
 * @param list Pointer to the head pointer of the token list.
 * @param data Pointer to the main data structure.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
t_bool	substitute_list(t_token **list, t_data *data)
{
	t_token	*token;

	token = *list;
	while (token && token->type != ANDOPER && token->type != OROPER)
	{
		if (token->type == TEXT)
		{
			if (!substitute_string(token, data->vars))
				return (FALSE);
			if (!token->str)
			{
				if (*list == token)
					*list = token->nxt;
				delete_link(&token);
				continue ;
			}
		}
		token = token->nxt;
	}
	return (expand_wildcards(list));
}
