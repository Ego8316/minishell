/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:42 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/10 18:27:09 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
t_bool	parse_token(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i];
	if (c == '(')
	{
		data->i++;
		data->depth++;
		printf("[PARSE DEBUG] Found '(' new depth: %i\n", data->depth * ((data->depth >= 0) * 2 - 1));
	}
	else if (c == ')')
	{
		data->i++;
		data->depth--;
		if (data->depth < 0)
		{
			printf("minishell: syntax error near unexpected token ')'");
			return (FALSE);
		}
		printf("[PARSE DEBUG] Found '(' new depth: %i\n", *depth * ((*depth >= 0) * 2 - 1));
	}
	else if (c == '|')
	{
		if (data->expect_cmd)
		{
			printf("\n");
			printf("minishell: syntax error near unexpected token '|'");
			return (FALSE);
		}
		data->i++;
		printf ("[PARSE DEBUG] Found pipe '|");
		if (data->cmd[data->i] == '|')
		{
			printf("|");
			(data->i)++;
		}
		data->expect_cmd = TRUE;
		printf("' at depth %i\n", data->depth);
	}
	else if (cmd[*i] == '&')
	{
		if (data->expect_cmd)
		{
			printf("\n");
			printf("minishell: syntax error near unexpected token '&'");
			return (FALSE);
		}
		data->i++;
		printf ("[PARSE DEBUG] Found pipe '&");
		if (data->cmd[data->i] == '&')
		{
			printf("&");
			(data->i)++;
		}
		data->expect_cmd = TRUE;
		printf("' at depth %i\n", data->depth);
	}
	return (TRUE);
}

static t_parse_data	get_parse_data(char *cmd)
{
	t_parse_data	data;

	data.cmd = cmd;
	data.i = 0;
	data.depth = 0;
	data.expect_cmd = FALSE;
	data.in_quotes = 0;
}

static void	get_more_data(t_parse_data *data)
{
	free(data.cmd);
	data.i = 0;
	data.cmd = readline("> ");
}

t_bool	parse_command(char *cmd)
{
	t_parse_data	data;

	data = get_parse_data(cmd);
	while (1)
	{
		if (!cmd[data->i])
		{
			if (data->depth == 0 && !data->expect_cmd)
				break ;
			get_more_data(data);
			continue ;
		}
		if (ft_isspace(cmd[i]))
		{
			i++;
			continue ;
		}
		if (!parse_token(cmd, *i, depth))
		{
			free(cmd);
			return (FALSE);
		}
	}
	free(cmd);
	return (TRUE);
}
*/

t_bool	parse_command(char *cmd)
{
	printf("%s\n", cmd);
	return (TRUE);
}

/* wot 
"(" ")" for priority
"|" "&" "||" "&&" pipes
">" "<" ">>" "<<" redirection
"$()" "$?" enviroment variaables
quoted stuff ''
double quoted stuff ""
*/
