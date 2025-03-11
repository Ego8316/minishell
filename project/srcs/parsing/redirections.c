/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:44 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 20:07:03 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	parse_redirection(t_parse_data *data)
{
	char	c;
	char	c2;

	c = data->cmd[data->i++];
	c2 = data->cmd[data->i];
	if (c == '>')
	{
		if (c2 != '>')
			return (token_add_last(REDIROUT, 0, &data->tokens));
		data->i++;
		return (token_add_last(OUTAPPEND, 0, &data->tokens));
	}
	else if (c == '<')
	{
		if (c2 != '<')
			return (token_add_last(REDIRIN, 0, &data->tokens));
		data->i++;
		return (token_add_last(INDELI, 0, &data->tokens));
	}
	return (FALSE);
}
