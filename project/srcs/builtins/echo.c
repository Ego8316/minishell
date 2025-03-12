/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:00 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 15:09:01 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the echo builtin:
 */
int	echo_builtin(t_token *args)
{
	t_bool	nl;

	nl = TRUE;
	while (args && args->type == TEXT && !ft_strcmp(args->str, "-n"))
	{
		nl = FALSE;
		args = args->nxt;
	}
	while (args && args->type==TEXT)
	{
		printf("%s", args->str);
		if (args->nxt && args->nxt->type==TEXT)
			printf(" ");
		args = args->nxt;
	}
	if (nl)
		printf("\n");
	return (0);
}
