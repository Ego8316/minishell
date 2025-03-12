/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:03:55 by ego               #+#    #+#             */
/*   Updated: 2025/03/12 20:56:27 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all there is to free in a NULL-terminated
 * array of strings and returns NULL.
 * 
 * @return NULL.
 */
void	*free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	return (NULL);
}

/**
 * @brief Frees all the variables' identifier and value
 * and returns 1.
 * 
 * @param vars Pointer to the var structure.
 * 
 * @return 1.
 */
int	free_vars(t_var *vars)
{
	t_var	*tmp;

	while (vars)
	{
		tmp = vars->nxt;
		if (vars->identifier)
			free(vars->identifier);
		if (vars->value)
			free(vars->value);
		free(vars);
		vars = tmp;
	}
	return (1);
}

/**
 * @brief Frees all there is to free in the data structure
 * and returns 1.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return 1.
 */
int	free_data(t_data *data)
{
	free_array(data->envp);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	free_vars(data->vars);
	return (1);
}

/**
 * @brief Frees the data structure and exits with provided status.
 * 
 * @param data Pointer to the data structure.
 * @param status Exit status.
 */
void	clean_exit(t_data *data, int status)
{
	free_data(data);
	exit(status);
}
