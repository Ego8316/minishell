/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:20 by ego               #+#    #+#             */
/*   Updated: 2025/03/14 18:03:17 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the exit builtin
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return 0 if success, 1 otherwise.
 */
int	exit_builtin(t_data *data, t_token *args)
{
	if (args->nxt)
		return (0);
	printf("exit\n");
	clean_exit(data, 0);
}
