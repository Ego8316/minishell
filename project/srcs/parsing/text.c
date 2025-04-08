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

static char *str_join_free(char *str, char *str2)
{
	char	*res;

	if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		str[0] = 0;
	}
	res = ft_strjoin(str, str2);
	if (str)
		free(str);
	return (res);
}

static char *append_str_free(char *str, char c)
{
	char	*append;

	append = malloc(sizeof(char) * 2);
	if (!append)
		return (0);
	append[0] = c;
	append[1] = 0;
	return (str_join_free(str, append));
}

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
		//printf("quotes parse loop on '%c' %i\n", data->cmd[data->i], data->i);
		c = data->cmd[data->i++];
		if (c == q)
			break;
		text = append_str_free(text, c);
		if (!text)
			return (0);
	}
	if (q == '\"')
		return (substitute_vars(text, data->vars));
	return (text);
}

static char	*parse_word(t_parse_data *data)
{
	char	*text;
	char	c;

	//printf("starting word parse with '%c'\n", data->cmd[data->i]);
	text = 0;
	while (1)
	{
		//printf("word parse loop on '%c' %i\n", data->cmd[data->i], data->i);
		c = data->cmd[data->i++];
		if (!c || ft_isspace(c) || is_char_oper(c) || c =='\'' || c == '\"')
			break;
		text = append_str_free(text, c);
		if (!text)
			return (0);
	}
	data->i--;
	//printf("ending word parse with '%s'\n", text);
	return (substitute_vars(text, data->vars));
}

t_bool	parse_text(t_parse_data *data)
{
	char	*text;
	char	c;

	data->expect_cmd = FALSE;
	text = 0;
	c = data->cmd[data->i];
	while (c && !ft_isspace(c) && !is_char_oper(c))
	{
		if (c == '\'' || c == '\"')
			text = str_join_free(text, parse_quote(data, c));
		else
			text = str_join_free(text, parse_word(data));
		if (!text)
			return (FALSE);
		c = data->cmd[data->i];
	}
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
