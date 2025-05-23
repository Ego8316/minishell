/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:41 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/23 14:07:21 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token_type(t_token_type type)
{
	if (type == UNDETERMINED)
		printf("UNDETERMINED");
	else if (type == TEXT)
		printf("TEXT");
	else if (type == PIPE)
		printf("PIPE |");
	else if (type == BGEXEC)
		printf("BGEXEC &");
	else if (type == OROPER)
		printf("OROPER ||");
	else if (type == ANDOPER)
		printf("ANDOPER &&");
	else if (type == REDIRIN)
		printf("REDIRIN <");
	else if (type == REDIROUT)
		printf("REDIROUT >");
	else if (type == OUTAPPEND)
		printf("OUTAPPEND >>");
	else if (type == INDELI)
		printf("INDELI <<");
}

void	print_token_list(t_token *tokens)
{
	while (tokens)
	{
		printf("Token type ");
		print_token_type(tokens->type);
		printf(" depth %i", tokens->depth);
		if (tokens->type == TEXT)
			printf(" '%s'", tokens->str);
		printf("\n");
		tokens = tokens->nxt;
	}
}

t_bool	debug_substitute(t_token **t, t_data *data)
{
	t_token	*token;

	printf("substituting tokens...\n");
	if (!*t)
		return (TRUE);
	if (!substitute_list(t, data))
		return (FALSE);
	token = *t;
	while (token)
	{
		while (token && token->type == TEXT)
			token = token->nxt;
		while (token && token->type != TEXT)
			token = token->nxt;
		if (!token)
			return (TRUE);
		if (!substitute_list(&token, data))
			return (FALSE);
	}
	return (TRUE);
}

void	run_cmd_from_user(t_data *d)
{
	char	*line;

	set_signals(1);
	line = readline(get_prompt(d, 1));
	set_signals(0);
	if (!line)
		clean_exit(d, 0);
	if (*line && !ft_stristype(line, ft_isspace) && try_parse_command(line, d))
	{
		d->ast = build_ast(d->tokens);
		if (g_last_exit_code == M_ERR)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		// print_ast(d->ast, 0, 1);
		g_last_exit_code = execute_ast(d, d->ast);
		// printf("--- exit code %i ---\n", g_last_exit_code);
		d->pipe = free_pipeline(d->pipe);
		if (g_last_exit_code == M_ERR)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		get_prompt(d, 2);
		d->ast = free_ast(d->ast);
	}
	free_str(&line);
	d->line++;
}
