/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:03:55 by ego               #+#    #+#             */
/*   Updated: 2025/04/01 16:13:53 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a string if it is not NULL and sets it to NULL.
 * 
 * @param s String to free.
 * 
 * @return NULL.
 */
void	*free_str(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

/**
 * @brief Frees all there is to free in a NULL-terminated
 * array of strings and returns NULL.
 * 
 * @return NULL.
 */
void	*free_array(char **arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		free_str(&arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

/**
 * @brief Frees all the variables' identifier and value
 * and returns NULL.
 * 
 * @param vars Pointer to the var structure.
 * 
 * @return NULL.
 */
void	*free_vars(t_var *vars)
{
	t_var	*tmp;

	while (vars)
	{
		tmp = vars->nxt;
		free_str(&vars->identifier);
		free_str(&vars->value);
		free(vars);
		vars = tmp;
	}
	return (NULL);
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
	free_str(&data->pwd);
	free_str(&data->oldpwd);
	free_vars(data->vars);
	if (data->tokens)
		token_free_list(&data->tokens);
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
