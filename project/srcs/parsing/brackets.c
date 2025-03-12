/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 14:03:15 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	parse_bracket(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i++];
	if (c == '(')
		data->depth++;
	else if (c == ')')
	{
		if (data->depth <= 0 || data->expect_cmd)
			return (syntax_error(data, data->i - 1));
		data->depth--;
	}
	else
		return (FALSE);
	return (TRUE);
}
