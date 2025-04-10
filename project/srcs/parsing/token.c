/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:17:50 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/09 21:52:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	nxt;
}					t_token;
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
	return (TRUE);
}

t_bool	token_free_list(t_token **list)
{
	t_token	*token;

	token = *list;
	while (token)
	{
		*list = token->nxt;
		free(token);
		token = *list;
	}
	return (FALSE);
}

t_bool	token_add_last(t_token_type type, char *str, int depth, t_token **list)
{
	t_token	*new;
	t_token	*loop;

	if (!token_make(type, str, depth, &new))
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
