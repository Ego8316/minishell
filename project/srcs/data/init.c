/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/13 02:35:08 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copies the envp variable and returns the
 * allocated copy.
 * 
 * @param envp Environment to be copied.
 * 
 * @return The allocated copy, NULL if allocation fails.
 */
static char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return ((char **)free_array(copy));
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static t_var	*copy_vars(char **envp)
{
	t_var	*head;
	t_var	*node;
	int		i;

	head = var_new_node(envp[0], ENV);
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
	data->envp = copy_envp(envp);
	data->pwd = getcwd(0, 0);
	data->oldpwd = ft_strdup(getenv("OLDPWD"));
	data->vars = copy_vars(envp);
	if (!data->envp || !data->pwd || !data->oldpwd || !data->vars)
		return (0);
	return (1);
}
