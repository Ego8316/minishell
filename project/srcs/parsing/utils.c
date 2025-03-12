/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:29:33 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 14:07:08 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_char_oper(char c)
{
	return (c == '|' || c == '&' || c == '>' ||
		c == '<' || c == '(' || c == ')');
}

t_bool	syntax_error(t_parse_data *data, int i)
{
	printf("minishell: syntax error near unexpected token '%c'\n", data->cmd[i]);
	printf("in command: '%s'\n", data->cmd);
	i += 13;
	while (i-- > 0)
		printf("%c", '-');
	printf("^\n");
	return (FALSE);
}
