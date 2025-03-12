/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:45 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:35:58 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *append_str(char *str, char c)
{
	char	*append;

	if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		str[0] = 0;
	}
	append = malloc(sizeof(char) * 2);
	if (!append)
		return (0);
	append[0] = c;
	append[1] = 0;
	return (ft_strjoin(str, append));
}

static char	*parse_double_quote(t_parse_data *data)
{
	char	*text;
	char	*old;
	char	c;

	text = 0;
	while (1)
	{
		while (!data->cmd[data->i])
			if (!expand_cmd(data))
				return (0);
		c = data->cmd[data->i++];
		if (c == '\"')
			break;
		old = text;
		if (c == '$')
			text = ft_strjoin(old, "VARPLACEHOLDER"); //add var parsing call later
		else
			text = append_str(old, c);
		if (old)
			free(old);
		if (!text)
			return (0);
	}
	return (text);
}

static char	*parse_single_quote(t_parse_data *data)
{
	char	*text;
	char	*old;
	char	c;

	text = 0;
	while (1)
	{
		while (!data->cmd[data->i])
			if (!expand_cmd(data))
				return (0);
		c = data->cmd[data->i++];
		if (c == '\'')
			break;
		old = text;
		text = append_str(old, c);
		if (old)
			free(old);
		if (!text)
			return (0);
	}
	return (text);
}

static char	*parse_word(t_parse_data *data)
{
	char	*text;
	char	*old;
	char	c;

	//printf("starting word parse with '%c'\n", data->cmd[data->i]);
	text = 0;
	while (1)
	{
		//printf("word parse loop on '%c' %i\n", data->cmd[data->i], data->i);
		c = data->cmd[data->i++];
		if (!c || ft_isspace(c) || is_char_oper(c))
			break;
		old = text;
		if (c == '\'')
			text = ft_strjoin(old, parse_single_quote(data));
		else if (c == '\"')
			text = ft_strjoin(old, parse_double_quote(data));
		else if (c == '$')
			text = ft_strjoin(old, "VARPLACEHOLDER"); //add var parsing call later
		else
			text = append_str(old, c);
		if (old)
			free(old);
		if (!text)
			return (0);
	}
	//printf("ending word parse with '%s'\n", text);
	return (text);
}

t_bool	parse_text(t_parse_data *data)
{
	char	*text;
	char	c;

	data->expect_cmd = FALSE;
	c = data->cmd[data->i++];
	if (c == '\'')
		text = parse_single_quote(data);
	else if (c == '\"')
		text = parse_double_quote(data);
	else
	{
		data->i--;
		text = parse_word(data);
		data->i--;
	}
	if (!text)
		return (FALSE);
	return (token_add_last(TEXT, text, data->depth, &data->tokens));
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
