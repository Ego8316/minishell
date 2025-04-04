/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:34 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 00:49:40 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Goes through envp to copy all environment variables.
 * Allocates memory for each node of the var linked list.
 * 
 * @param envp Environment variables to be copied.
 * 
 * @return Pointer to the head of the var list, NULL if allocation fails.
 */
static t_var	*copy_vars(char **envp)
{
	t_var	*head;
	t_var	*node;
	int		i;

	head = var_new_node_line(envp[0], ENV);
	if (!head)
		return (NULL);
	node = head;
	i = 1;
	while (envp[i])
	{
		if (!var_add_line(&node, envp[i], ENV))
			return (free_vars(head));
		node = node->nxt;
		i++;
	}
	return (head);
}

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
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
		data->oldpwd = NULL;
	else
	{
		data->oldpwd = ft_strdup(oldpwd);
		if (!data->oldpwd)
			return (0);
	}
	data->envp = NULL;
	data->pwd = getcwd(0, 0);
	data->vars = copy_vars(envp);
	data->tokens = NULL;
	if (!data->pwd || !data->vars)
		return (0);
	return (1);
}
