/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:41 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/01 17:16:52 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets and runs a command from user.
 */

static void print_token_type(t_token_type type)
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
	else if (type == UNRESOLVED_TEXT)
		printf("UNRESOLVED_TEXT");
}

void print_token_list(t_token *tokens)
{
	while (tokens)
	{
		printf("Token type ");
		print_token_type(tokens->type);
		printf(" depth %i", tokens->depth);
		if (tokens->type == TEXT || tokens->type == UNRESOLVED_TEXT)
			printf(" '%s'", tokens->str);
		printf("\n");
		tokens = tokens->nxt;
	}
}

void	run_cmd_from_user(t_data *d)
{
	if (!try_parse_command(readline("[minishell]: "), d))
		printf("Fatal error parsing command!\n");
	else
		print_token_list(d->tokens);
	if (!d->tokens)
		return ;
	execute_commands(d, d->tokens);
}
