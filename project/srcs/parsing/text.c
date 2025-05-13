/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:45 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/08 22:04:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	parse_quote(t_parse_data *data, char q, char **text)
{
	char	c;

	while (1)
	{
		while (!data->cmd[data->i])
			if (!expand_cmd(data))
				return (0);
		c = data->cmd[data->i++];
		if (!strb_append(text, c))
			return (FALSE);
		if (c == q)
			break ;
	}
	return (TRUE);
}

static t_bool	parse_word(t_parse_data *data, char **text)
{
	char	c;

	while (1)
	{
		c = data->cmd[data->i++];
		if (!c || ft_isspace(c) || is_char_oper(c) || c == '\'' || c == '\"')
			break ;
		if (!strb_append(text, c))
			return (FALSE);
	}
	data->i--;
	return (TRUE);
}

t_bool	parse_text(t_parse_data *data)
{
	char	*text;
	char	c;
	t_token	*token;

	data->expect_cmd = FALSE;
	text = 0;
	c = data->cmd[data->i];
	while (c && !ft_isspace(c) && !is_char_oper(c))
	{
		if (c == '\'' || c == '\"')
		{
			if (!parse_quote(data, c, &text))
				return (FALSE);
		}
		else if (!parse_word(data, &text))
			return (FALSE);
		c = data->cmd[data->i];
	}
	return (token_make(TEXT, text, data->depth, &token)
		&& token_add_last(token, &data->tokens));
}
/*
typedef struct s_parse_data
{
	char	*cmd;
	int		i;
	t_bool	expect_cmd;
	char	*arg;
	int		depth;
	t_token *tokens;
}			t_parse_data;
return (token_add_last(OROPER, 0, data->depth, &data->tokens));
*/
