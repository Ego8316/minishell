/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:31:47 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 14:02:48 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	mk_tk(t_parse_data *d, t_token_type a, t_token_type b, char c)
{
	t_token	*token;

	if (d->cmd[d->i] != c)
		return (token_make(a, 0, d->depth, &token)
			&& token_add_last(token, &d->tokens));
	d->i++;
	return (token_make(b, 0, d->depth, &token)
		&& token_add_last(token, &d->tokens));
}

t_bool	parse_operator(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i++];
	if (data->expect_cmd && !ft_strchr("<>", c)
		&& !ft_strchr("<>", data->cmd[data->i]))
		return (syntax_error(data, data->i - 1));
	data->expect_cmd = TRUE;
	if (c == '&')
		return (mk_tk(data, BGEXEC, ANDOPER, '&'));
	else if (c == '|')
		return (mk_tk(data, PIPE, OROPER, '|'));
	else if (c == '>')
		return (mk_tk(data, REDIROUT, OUTAPPEND, '>'));
	else if (c == '<')
		return (mk_tk(data, REDIRIN, INDELI, '<'));
	return (FALSE);
}
