/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:35:52 by ego               #+#    #+#             */
/*   Updated: 2025/03/18 15:16:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the directory to the value stored in HOME.
 * If HOME is not set, displays an error message. Otherwise,
 * changes the directory and updates the var list and data
 * pwd and oldpwd. Exits the program in case of allocation
 * failure.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return The exit code.
 */
static int	cd_home(t_data *data)
{
	t_var	*home;

	home = var_get(&data->vars, "HOME");
	if (!home)
		return (errmsg("minishell: cd: HOME not set\n", 0, 0, 1));
	chdir(home->value);
	if (errno)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home->value);
		return (errno);
	}
	free(data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	return (0);
}

/**
 * @brief Changes the directory to the value stored in OLDPWD.
 * If OLDPWD is not set, displays an error message. Otherwise,
 * changes the directory and updates the var list and data
 * pwd and oldpwd. Exits the program in case of allocation
 * failure. If everything went fine, displays the new path.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return The exit code.
 */
static int	cd_oldpwd(t_data *data)
{
	t_var	*oldpwd;
	char	*tmp;

	oldpwd = var_get(&data->vars, "OLDPWD");
	if (!oldpwd)
		return (errmsg("minishell: cd: OLDPWD not set\n", 0, 0, 1));
	chdir(oldpwd->value);
	if (errno)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(oldpwd->value);
		return (errno);
	}
	tmp = data->oldpwd;
	data->oldpwd = data->pwd;
	data->pwd = tmp;
	if (!var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	printf("%s\n", data->pwd);
	return (0);
}

/**
 * @brief Executes the cd builtin:
 * No argument: cd $HOME
 * 	- if HOME not set: HOME not set
 *  - if HOME modified, still does it
 * 		TO HANDLE MANUALLY
 * Argument: -
 *  - goes to OLDPWD and prints it
 *  - if OLDPWD not set: OLDPWD not set
 * 		TO HANDLE MANUALLY
 *  More than one argument: too many arguments
 * Any other stuff can just be sent to chdir
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return 0 if success, 1 otherwise.
 */
int	cd_builtin(t_data *data, t_token *args)
{
	if (!args || args->type != TEXT)
		return (cd_home(data));
	if (args && args->type == TEXT && args->nxt && args->nxt->type == TEXT)
		return (errmsg("minishell: cd: too many arguments\n", 0, 0, 1));
	if (args && args->type == TEXT && !*args->str)
		return (0);
	if (args && args->type == TEXT && !ft_strcmp(args->str, "-"))
		return (cd_oldpwd(data));
	chdir(args->str);
	if (errno)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(args->str);
		return (errno);
	}
	free(data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	return (0);
}
