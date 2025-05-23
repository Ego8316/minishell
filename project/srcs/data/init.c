/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:34 by ego               #+#    #+#             */
/*   Updated: 2025/05/23 15:48:37 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a string is a valid integer. Skips all leading white spaces,
 * accepts only one plus or minus sign, and then ensures there are only digits
 * afterwards.
 * 
 * @param nptr String to be checked.
 * 
 * @return 1 if it is a valid integer, 0 otherwise.
 */
static int	is_valid_integer(char *nptr)
{
	int	i;

	if (!nptr)
		return (0);
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
		i++;
	return (nptr[i] == '\0');
}

/**
 * @brief Prints a warning when shell level is  too high.
 * 
 * Mimics the warning behavior of Bash when the shell level exceeds 999.
 * 
 * @param shlvl Previous shell level value.
 * 
 * @return Always returns 0 for convenience.
 */
static int	put_shell_level_warning(int shlvl)
{
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putnbr_fd(shlvl + 1, STDERR_FILENO);
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
	return (0);
}

/**
 * @brief Copies all environment variables from the given environment string
 * array into a linked list of `t_var` nodes. Allocates memory for each node.
 * 
 * @param envp Environment variables to be copied from.
 * 
 * @return Pointer to the head of the newly created linked list of variables,
 * NULL if allocation fails or the environment is empty.
 */
static t_var	*copy_vars(char **envp)
{
	t_var	*head;
	t_var	*node;
	int		i;

	if (!*envp)
		return (NULL);
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
 * @brief Updates the environment variable `SHLVL`. If it is not set, sets it
 * to 1. If it is set but contains at least one non-digit character, replaces
 * it by 1. Otherwise increments its integer value by 1.
 * 
 * @param vars Pointer to the var list.
 * 
 * @return 1 if the operation is successful, 0 if allocation fails.
 */
static int	update_shell_level(t_var **vars)
{
	t_var	*shlvl;
	int		prev;

	shlvl = var_get(vars, "SHLVL");
	if (!shlvl || !*shlvl->value || !is_valid_integer(shlvl->value))
		return (var_set(vars, "SHLVL", "1"));
	prev = ft_atoi(shlvl->value);
	free_str(&shlvl->value);
	if (prev < 0)
		return (var_set(vars, "SHLVL", "0"));
	if (prev >= 999)
		prev = put_shell_level_warning(prev);
	shlvl->value = ft_itoa(prev + 1);
	if (!shlvl->value)
		return (0);
	return (1);
}

/**
 * @brief Initializes the main data structure by setting up necessary fields
 * such as `pwd`, `oldpwd`, environment variables, and prompt information.
 * 
 * @param data Pointer to the main data structure to be initialized.
 * @param envp Startup environment variables.
 * 
 * @return 0 if memory allocation fails, 1 otherwise.
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
	data->pwd = getcwd(0, 0);
	data->vars = copy_vars(envp);
	data->tokens = NULL;
	data->pipe = NULL;
	data->ast = NULL;
	data->line = 1;
	data->prefix = get_prefix();
	if (!data->pwd || (!data->vars && *envp) || !data->prefix
		|| !update_shell_level(&data->vars))
		return (0);
	get_prompt(data, 0);
	get_prompt(data, 2);
	return (1);
}
