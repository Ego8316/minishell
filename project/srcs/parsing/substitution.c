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
