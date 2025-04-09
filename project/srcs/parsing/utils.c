/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:29:33 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/09 21:22:11 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_char_oper(char c)
{
	return (c == '|' || c == '&' || c == '>'
		|| c == '<' || c == '(' || c == ')');
}

t_bool	syntax_error(t_parse_data *data, int i)
{
	g_last_exit_code = errmsg("minishell: syntax error near unexpected token `",
			&data->cmd[i], "'\n", 2);
	printf("in command: '%s'\n", data->cmd);
	i += 13;
	while (i-- > 0)
		printf("%c", '-');
	printf("^\n");
	return (FALSE);
}
