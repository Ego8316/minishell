/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:34 by ego               #+#    #+#             */
/*   Updated: 2025/05/23 16:11:00 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the `pwd` builtin command: prints the current working
 * directory.
 * 
 * @param data Pointer to the main data structure.
 * @param argv Arguments (should not be any).
 * 
 * @return Exit status: 0 if the operation is successful (always).
 */
int	pwd_builtin(t_data *data, char **argv)
{
	(void)argv;
	ft_putendl_fd(data->pwd, STDOUT_FILENO);
	return (0);
}
