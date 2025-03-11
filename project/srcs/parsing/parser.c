/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:42 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 20:03:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd(t_parse_data *data)
{
	char	*new;
	char	*current;

	current = data->cmd;
	new = readline("> ");
	data->cmd = ft_strjoin(current, new);
	free(new);
	free(current);
}

static int	parse_loop(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i];
	if (!c)
		return (-1);
	if (c == '|' || c == '&')
		return (parse_pipe(data));
	if (c == '>' || c == '<')
		return (parse_redirection(data));
	return (0);
}

/**
 * @brief Tries to parse a command from the user.
 * Gets more prompts if needed.
 * 
 * @param cmd Command from user 
 * @param out_tokens Give this a pointer to a t_token * variable
 * that it will return the list of tokens to.
 * 
 * @return Returns true if successful.
 * Returns false on malloc and syntax errors.
 */
t_bool	try_parse_command(char *cmd, t_token **out_tokens)
{
	t_parse_data	data;
	int	ret;

	*out_tokens = 0;
	if (!cmd)
		return (TRUE);
	data.cmd = cmd;
	data.i = 0;
	data.tokens = FALSE;
	data.expect_cmd = FALSE;
	data.tokens = 0;
	data.arg = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = parse_loop(&data);
		if (!ret)
		{
			free (data.cmd);
			return (token_free_list(&data.tokens));
		}
	}
	free(data.cmd);
	*out_tokens = data.tokens;
	return (TRUE);
}

/* wot 
"|" "&" "||" "&&" pipes
">" "<" ">>" "<<" redirection
"$" "$?" enviroment variables
quoted stuff ''
double quoted stuff ""
*/

/**
 * @brief Copies the envp variable and returns the
 * 
 * @param envp Environment to be copied.
 * 
 * @return The allocated copy, NULL if allocation fails.
 */

/*
typedef struct s_parse_data
{
	char	*cmd;
	int		i;
	t_bool	expect_cmd;
	char	*arg;
	t_token *tokens;
}			t_parse_data;
*/
