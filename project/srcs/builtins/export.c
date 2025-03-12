/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:27 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 13:41:23 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the export builtin: tries and put the given variable and its
 * value in the environment. If no argument given, does not do anything as it
 * is mentioned in the manual export's behaviour with no argument is undefined.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return 0 on success, 1 otherwise.
 */
int	export_builtin(t_data *data, t_token *args)
{
	int	i;

	if (!args->nxt)
	{
		printf("\n");
		return (0);
	}
}
