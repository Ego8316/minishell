/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:31:47 by pkurt             #+#    #+#             */
/*   Updated: 2025/11/30 22:31:11 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates and appends an operator token, handling double-character ops.
 *
 * If the current character matches `c`, creates a single-character token of
 * type `a`; otherwise consumes the next character and creates a double token
 * of type `b`.
 *
 * @param d Parser state container.
 * @param a Token type for the single-character operator.
 * @param b Token type for the double-character operator.
 * @param c Character representing the operator.
 *
 * @return TRUE on successful token creation and insertion, FALSE otherwise.
 */
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

/**
 * @brief Parses an operator token from the current position.
 *
 * Validates placement (ensuring it follows a command when required) and
 * creates the appropriate token for single or double operators such as `|`,
 * `||`, `&`, `&&`, `>`/`>>`, and `<`/`<<`.
 *
 * @param data Parser state container.
 *
 * @return TRUE on success, FALSE on syntax error or allocation failure.
 */
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
