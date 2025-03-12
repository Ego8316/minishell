/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 15:25:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the pwd builtin: simply prints
 * the working directory.
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return Exit status.
 */
int	pwd_builtin(t_data *data, t_token *args)
{
	(void)args;
	printf("%s\n", data->pwd);
	return (0);
}
