/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:13:57 by ego               #+#    #+#             */
/*   Updated: 2025/05/19 19:53:52 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_data *d, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == CMD)
		return (execute_pipeline(d, node->cmd));
	g_last_exit_code = execute_ast(d, node->left);
	if (g_last_exit_code == M_ERR)
		clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
	d->pipe = free_pipeline(d->pipe);
	if (node->type == AND)
	{
		if (g_last_exit_code == 0)
			return (execute_ast(d, node->right));
		return (g_last_exit_code);
	}
	else if (node->type == OR)
	{
		if (g_last_exit_code != 0)
			return (execute_ast(d, node->right));
		return (g_last_exit_code);
	}
	return (g_last_exit_code);
}
