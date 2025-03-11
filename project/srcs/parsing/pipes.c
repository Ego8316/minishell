/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:43 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 20:06:31 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	parse_pipe(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i++];
	if (data->expect_cmd)
	{
		printf("minishell: syntax error near unexpected token '%c'", c);
		return (FALSE);
	}
	data->expect_cmd = TRUE;
	if (c == '|')
	{
		if (data->cmd[data->i] != '|')
			return (token_add_last(PIPE, 0, &data->tokens));
		data->i++;
		return (token_add_last(OROPER, 0, &data->tokens));
	}
	else if (c == '&')
	{
		if (data->cmd[data->i] != '&')
			return (token_add_last(BGEXEC, 0, &data->tokens));
		data->i++;
		return (token_add_last(ANDOPER, 0, &data->tokens));
	}
	return (FALSE);
}
