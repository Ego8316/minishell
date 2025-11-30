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

/**
 * @brief Appends a quoted segment to the token text buffer.
 *
 * Copies characters until the matching quote is found, expanding the command
 * buffer if needed when encountering line continuations.
 *
 * @param data Parser state container.
 * @param q Quote character that opened the segment.
 * @param text Destination string builder.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
static t_bool	parse_quote(t_parse_data *data, char q, char **text)
{
	char	c;

	if (!strb_append(text, q))
		return (FALSE);
	data->i++;
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

/**
 * @brief Consumes a non-quoted word from the command string.
 *
 * Copies characters until whitespace, an operator, or a quote is encountered.
 *
 * @param data Parser state container.
 * @param text Destination string builder.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
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

/**
 * @brief Parses a TEXT token starting at the current position.
 *
 * Aggregates quoted segments and plain words into a single token and appends
 * it to the token list.
 *
 * @param data Parser state container.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
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
