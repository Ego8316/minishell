/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:23:42 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 14:17:07 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all there is to free in a command structure
 * array of strings and returns NULL.
 * 
 * @param cmd Command structure to free.
 * 
 * @return NULL.
 */
void	*free_command(t_command *cmd)
{
	free_str(&cmd->name);
	free_str(&cmd->pathname);
	if (cmd->heredoc_name)
		unlink(cmd->heredoc_name);
	free_str(&cmd->heredoc_name);
	free_array(cmd->argv);
	free(cmd);
	return (NULL);
}
