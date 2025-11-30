/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:42 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/25 20:39:28 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prompts for an additional line when a command is incomplete.
 *
 * Appends a newline to the current buffer, reads the continuation with
 * `readline("> ")`, and concatenates it. Exits cleanly on EOF.
 *
 * @param data Parser state container.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
t_bool	expand_cmd(t_parse_data *data)
{
	char	*new;
	char	*current;

	current = data->cmd;
	data->cmd = ft_strjoin(current, "\n");
	free(current);
	if (!data->cmd)
		return (FALSE);
	current = data->cmd;
	new = readline("> ");
	if (new)
		data->cmd = ft_strjoin(current, new);
	free(new);
	free(current);
	if (!new)
	{
		token_free_list(&(data->tokens));
		clean_exit(data->data, 0);
	}
	return (data->cmd != 0);
}

/**
 * @brief Initializes a parsing context from the raw command.
 *
 * Sets indices, depth, expected token state, variable list, and backpointer to
 * the main data structure.
 *
 * @param cmd Command string to parse.
 * @param d Pointer to the main shell data structure.
 *
 * @return Fully initialized parse data structure.
 */
static t_parse_data	get_parse_data(char *cmd, t_data *d)
{
	t_parse_data	data;

	data.cmd = cmd;
	data.i = 0;
	data.tokens = FALSE;
	data.expect_cmd = FALSE;
	data.tokens = 0;
	data.depth = 0;
	data.vars = d->vars;
	data.data = d;
	return (data);
}

/**
 * @brief Dispatches parsing based on the current character.
 *
 * Handles whitespace, operators, brackets, and text parsing. Requests more
 * input when encountering an unexpected end of command.
 *
 * @param data Parser state container.
 *
 * @return Parser progress flag: positive on continue, 0 on error, -1 when a
 * complete command at depth 0 is reached.
 */
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
		return (1 + (0 * data->i++));
	if (c == '|' || c == '&' || c == '>' || c == '<')
		return (parse_operator(data));
	if (c == '(' || c == ')')
		return (parse_bracket(data));
	return (parse_text(data));
}

/**
 * @brief Main parsing loop that builds the token list.
 *
 * Iterates through the command string, keeping track of nested depth and
 * stopping when the current bracket group is finished.
 *
 * @param data Parser state container.
 *
 * @return TRUE on success, FALSE on allocation or syntax error.
 */
t_bool	parse_loop(t_parse_data *data)
{
	int		ret;
	int		prev_depth;

	prev_depth = data->depth;
	ret = 1;
	while (ret > 0 && (prev_depth == 0 || data->depth >= prev_depth))
	{
		ret = parse_char(data);
		if (!ret)
			return (FALSE);
	}
	data->depth = prev_depth - (prev_depth > 0);
	data->expect_cmd = FALSE;
	return (TRUE);
}

/**
 * @brief Parses the user input into a token list.
 *
 * Coordinates parsing, handles errors, and stores the resulting tokens in the
 * main data structure. On failure, frees temporary buffers and tokens.
 *
 * @param cmd Pointer to the raw command string (freed on exit).
 * @param d Pointer to the main data structure.
 *
 * @return TRUE on success, FALSE on allocation or syntax error.
 */
t_bool	try_parse_command(char **cmd, t_data *d)
{
	t_parse_data	data;

	if (!*cmd)
		return (TRUE);
	data = get_parse_data(*cmd, d);
	if (!parse_loop(&data))
	{
		free_str(&data.cmd);
		*cmd = 0;
		return (token_free_list(&(data.tokens)));
	}
	add_history(data.cmd);
	free_str(&data.cmd);
	*cmd = 0;
	d->tokens = data.tokens;
	return (TRUE);
}
