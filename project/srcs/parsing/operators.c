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

t_bool	parse_greater_symbol(t_parse_data *data)
{
	if (data->cmd[data->i] != '>')
		return (token_add_last(REDIROUT, 0, data->depth, &data->tokens));
	data->i++;
	return (token_add_last(OUTAPPEND, 0, data->depth, &data->tokens));
}

t_bool	parse_lesser_symbol(t_parse_data *data)
{

	if (data->cmd[data->i] != '<')
		return (token_add_last(REDIRIN, 0, data->depth, &data->tokens));
	data->i++;
	return (token_add_last(INDELI, 0, data->depth, &data->tokens));
}

t_bool	parse_and_symbol(t_parse_data *data)
{

	if (data->cmd[data->i] != '&')
		return (token_add_last(BGEXEC, 0, data->depth, &data->tokens));
	data->i++;
	return (token_add_last(ANDOPER, 0, data->depth, &data->tokens));
}

t_bool	parse_pipe_symbol(t_parse_data *data)
{
	if (data->cmd[data->i] != '|')
		return (token_add_last(PIPE, 0, data->depth, &data->tokens));
	data->i++;
	return (token_add_last(OROPER, 0, data->depth, &data->tokens));
}

t_bool	parse_operator(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i++];
	if (data->expect_cmd)
		return (syntax_error(data, data->i - 1));
	data->expect_cmd = TRUE;
	if (c == '&')
		return (parse_and_symbol(data));
	else if (c == '|')
		return (parse_pipe_symbol(data));
	else if (c == '>')
		return (parse_greater_symbol(data));
	else if (c == '<')
		return (parse_lesser_symbol(data));
	return (FALSE);
}
