/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:34 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 14:08:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the pwd builtin: simply prints
 * the working directory.
 * 
 * @param data Pointer to the data structure.
 * @param argv Arguments.
 * 
 * @return Exit status.
 */
int	pwd_builtin(t_data *data, char **argv)
{
	(void)argv;
	printf("%s\n", data->pwd);
	return (0);
}
