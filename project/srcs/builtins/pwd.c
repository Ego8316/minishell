/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/11 18:15:10 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the pwd builtin: simply prints
 * the working directory.
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments (should not be any).
 * 
 * @return Exit status.
 */
int	pwd_builtin(t_data *data, char **args)
{
	if (args && args[0])
		return (errmsg("pwd: Too many arguments.\n", 0, 0, 1));
	printf("%s\n", data->pwd);
	return (0);
}
