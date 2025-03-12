/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:42 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:34:18 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	expand_cmd(t_parse_data *data)
{
	char	*new;
	char	*current;

	current = data->cmd;
	data->cmd = ft_strjoin(current, " ");
	free(current);
	if (!data->cmd)
		return (FALSE);
	current = data->cmd;
	new = readline("> ");
	data->cmd = ft_strjoin(current, new);
	free(new);
	free(current);
	return (data->cmd != 0);
}

static t_parse_data	get_parse_data(char *cmd)
{
	t_parse_data	data;
	data.cmd = cmd;
	data.i = 0;
	data.tokens = FALSE;
	data.expect_cmd = FALSE;
	data.tokens = 0;
	data.depth = 0;
	return (data);
}

static int	parse_char(t_parse_data *data)
{
	char	c;

	c = data->cmd[data->i];
	if (!c)
	{
		if (!data->expect_cmd && data->depth <= 0)
			return (-1);
		return (expand_cmd(data));
	}
	if (ft_isspace(c))
		return (1 + data->i++ * 0);
	if (c == '|' || c == '&' || c == '>' || c == '<')
		return (parse_operator(data));
	if (c == '(' || c == ')')
		return (parse_bracket(data));
	return (parse_text(data));
}

t_bool	parse_loop(t_parse_data *data)
{
	int		ret;
	int		prev_depth;
	t_bool	prev_expect_cmd;

	prev_depth = data->depth;
	prev_expect_cmd = data->expect_cmd;
	ret = 1;
	while (ret > 0 && (prev_depth == 0 || data->depth >= prev_depth))
	{
		ret = parse_char(data);
		if (!ret)
			return (FALSE);
	}
	data->depth = prev_depth - (prev_depth > 0);
	data->expect_cmd = prev_expect_cmd;
	return (TRUE);
}

/**
 * @brief Tries to parse a command from the user.
 * Gets more prompts if needed.
 * 
 * @param cmd Starting command from user 
 * @param out_tokens Give this a pointer to a t_token * variable
 * that it will return the list of tokens to.
 * 
 * @return Returns true if successful.
 * Returns false on malloc and syntax errors.
 */
t_bool	try_parse_command(char *cmd, t_token **out_tokens)
{
	t_parse_data	data;

	*out_tokens = 0;
	if (!cmd)
		return (TRUE);
	data = get_parse_data(cmd);
	if (!parse_loop(&data))
	{
		free (data.cmd);
		return (token_free_list(&(data.tokens)));
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
	int		depth;
	t_token *tokens;
}			t_parse_data;
*/
