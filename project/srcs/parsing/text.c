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

static char	*parse_quote(t_parse_data *data, char q)
{
	char	*text;
	char	c;

	text = 0;
	data->i++;
	while (1)
	{
		while (!data->cmd[data->i])
			if (!expand_cmd(data))
				return (0);
		c = data->cmd[data->i++];
		if (c == q && (q != '\"' || isnescp(data->cmd, data->i - 1, q)))
			break;
		if (q != '\"' || c != '\\' || data->cmd[data->i] != q)
			if (!strb_append(&text, c))
				return (0);
	}
	if (q == '\"')
		return (substitute_stuff(text, data->vars, 0, -1));
	return (text);
}

static char	*parse_word(t_parse_data *data, int **wcs, int wcs_off)
{
	char	*text;
	char	c;

	text = 0;
	while (1)
	{
		//printf("word parse loop on '%c' %i\n", data->cmd[data->i], data->i);
		c = data->cmd[data->i++];
		if (!c || ft_isspace(c) || is_char_oper(c) || c == '\'' || c == '\"')
			break;
		if (!strb_append(&text, c))
			return (0);
	}
	data->i--;
	return (substitute_stuff(text, data->vars, wcs, wcs_off));
}

t_bool	parse_text(t_parse_data *data)
{
	char	*text;
	char	c;
	int		*wcs;
	t_token	*token;

	wcs = 0;
	data->expect_cmd = FALSE;
	text = 0;
	c = data->cmd[data->i];
	while (c && !ft_isspace(c) && !is_char_oper(c))
	{
		if (isnescp(data->cmd, data->i, '\'') || isnescp(data->cmd, data->i, '\"'))
			strb_join(&text, parse_quote(data, c));
		else
			strb_join(&text, parse_word(data, &wcs, ft_strlen_null(text)));
		if (!text)
			return (FALSE);
		c = data->cmd[data->i];
	}
	if (!token_make(TEXT, text, data->depth, &token))
		return (FALSE);
	token->wilds = wcs;
	return (token_add_last(token, &data->tokens));
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
