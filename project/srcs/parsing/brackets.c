/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:48:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_last_token_depth(t_token *token)
{
	while (token && token->nxt)
		token = token->nxt;
	if (!token)
		return (0);
	return (token->depth);
}

t_bool	parse_bracket(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i++];
	if (c == '(')
	{
		data->depth++;
		return (parse_loop(data));
	}
	else if (c == ')')
	{
		if (data->depth <= 0 || data->expect_cmd)
			return (syntax_error(data, data->i - 1));
		data->depth--;
		if (get_last_token_depth(data->tokens) <= data->depth)
			return (syntax_error(data, data->i - 1));
	}
	else
		return (FALSE);
	return (TRUE);
}
