/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/11 13:06:38 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the data structure.
 * 
 * @param data Pointer to the data structure.
 * @param envp Startup environment.
 * 
 * @return 0 if allocation fails, 1 otherwise.
 */
t_bool	data_init(t_data *data, char **envp)
{
	data->envp = copy_envp(envp);
	data->pwd = getcwd(0, 0);
	data->oldpwd = getenv("OLDPWD");
	if (!data->envp || !data->pwd || !data->oldpwd)
		return (0);
	return (1);
}
