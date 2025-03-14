/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:41 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/14 13:52:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets and runs a command from user.
 */

/*
typedef enum e_token_type
{
	UNDETERMINED = 0,
	TEXT = 1,
	PIPE = 2,
	BGEXEC = 3,
	OROPER = 4,
	ANDOPER = 5,
	REDIRIN = 6,
	REDIROUT = 7,
	OUTAPPEND = 8,
	INDELI = 9
}	t_token_type;
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
}

void	run_cmd_from_user(void)
{
	t_token *tokens;
	t_token *check;

	if (try_parse_command(readline("[minishell]: "), &tokens))
	{
		check = tokens;
		while (check)
		{
			printf("Token type ");
			print_token_type(check->type);
			printf(" depth %i", check->depth);
			if (check->type == TEXT)
				printf(" '%s'", check->str);
			printf("\n");
			check = check->nxt;
		}
		token_free_list(&tokens);
	}
}
