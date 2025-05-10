/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:46 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/10 18:40:29 by ego              ###   ########.fr       */
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

static t_bool	substitute_string(t_token *t, t_var *vars)
{
	int		i;
	char	*new;

	i = 0;
	new = 0;
	printf("substituting '%s'\n", t->str);
	while (t->str[i])
	{
		if (t->str[i] == '\'' || t->str[i] == '\"')
		{
			if (!substitute_quote(t, &new, &i, vars))
				return (FALSE);
		}
		else if (t->str[i] == '$')
		{
			if (!substitute_var(t->str, &i, vars, &new))
				return (FALSE);
		}
		else
		{
			if (!record_wildcard(i, &t->wilds))
				return (FALSE);
			if (!strb_append(&new, t->str[i++]))
				return (FALSE);
		}
	}
	if (!new)
		new = strb_new();
	free(t->str);
	t->str = new;
	printf("new '%s'\n", t->str);
	return(TRUE);
}

t_bool	substitute_list(t_token **list, t_data *data)
{
	t_token	*token;

	token = *list;
	while (token && token->type == TEXT)
	{
		if (!substitute_string(token, data->vars))
			return (FALSE);
		token = token->nxt;
	}
	return (expand_wildcards(list));
}
