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

/**
 * @brief Returns the depth of the last token in a list.
 *
 * Walks to the tail of the token list and returns its depth, or 0 if the list
 * is empty.
 *
 * @param token Head of the token list.
 *
 * @return Depth value of the last token, 0 when the list is empty.
 */
static int	get_last_token_depth(t_token *token)
{
	while (token && token->nxt)
		token = token->nxt;
	if (!token)
		return (0);
	return (token->depth);
}

/**
 * @brief Parses a single bracket character and updates parser state.
 *
 * Increments depth on '(', decrements on ')', and triggers syntax errors for
 * unexpected closing brackets or mismatched depths. On '(', resumes parsing
 * recursively to allow nested groups.
 *
 * @param data Parser state container.
 *
 * @return TRUE on success, FALSE on syntax error.
 */
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
