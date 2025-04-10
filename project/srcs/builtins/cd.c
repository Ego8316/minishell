/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:35:52 by ego               #+#    #+#             */
/*   Updated: 2025/04/10 19:16:34 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief First tries to get HOME from the environment that was given
 * to minishell at startup. If not available, tries and get USER to
 * rebuild HOME. If not available, give /home.
 * 
 * @return Allocated path to home directory, NULL if allocation fails.
 */
static char	*get_home_fallback(void)
{
	char	*home_env;
	char	*user_env;

	home_env = getenv("HOME");
	if (home_env)
		return (ft_strdup(home_env));
	user_env = getenv("USER");
	if (user_env)
		return (ft_strjoin("/home/", user_env));
	return (ft_strdup("/home"));
}

/**
 * @brief In the case where HOME is not set but cd ~ is used, minishell
 * will attempt to make the home directory from the username and then
 * go to that directory. It also first checks in the environment if
 * HOME is there (set at startup but unset by user).
 * 
 * @param data Pointer to the data structure.
 * 
 * @return The exit code, -2 if allocation fails.
 */
static int	cd_home_fallback(t_data *data)
{
	char	*home;

	home = get_home_fallback();
	if (!home)
		return (M_ERR);
	free(data->oldpwd);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home);
		return (free_str(&home), errno);
	}
	free_str(&home);
	free_str(&data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		return (M_ERR);
	return (0);
}

/**
 * @brief Changes the directory to the value stored in HOME.
 * If HOME is not set, displays an error message. Otherwise,
 * changes the directory and updates the var list and data
 * pwd and oldpwd. Exits the program in case of allocation
 * failure.
 * 
 * @param data Pointer to the data structure.
 * @param fallback Whether minishell should get the home directory
 * from the username if HOME is not set.
 * 
 * @return The exit code, -2 if allocation fails.
 */
static int	cd_home(t_data *data, int fallback)
{
	t_var	*home;

	home = var_get(&data->vars, "HOME");
	if (!home && fallback)
		return (cd_home_fallback(data));
	if (!home)
		return (errmsg("minishell: cd: HOME not set\n", 0, 0, 1));
	if (!*home->value)
		return (0);
	if (chdir(home->value) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home->value);
		return (errno);
	}
	free_str(&data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		return (M_ERR);
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
 * @return The exit code, -2 if allocation fails.
 */
static int	cd_oldpwd(t_data *data)
{
	t_var	*oldpwd;

	oldpwd = var_get(&data->vars, "OLDPWD");
	if (!oldpwd)
		return (errmsg("minishell: cd: OLDPWD not set\n", 0, 0, 1));
	if (!*oldpwd->value)
	{
		printf("\n");
		if (!var_set(&data->vars, "OLDPWD", data->pwd))
			return (M_ERR);
		return (0);
	}
	if (chdir(oldpwd->value) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(oldpwd->value);
		return (errno);
	}
	swap_str(&data->oldpwd, &data->pwd);
	if (!var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		return (M_ERR);
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
 * @param argv Arguments.
 * 
 * @return 0 if success, 1 otherwise, -2 if allocation fails.
 */
int	cd_builtin(t_data *data, char **argv)
{
	if (!*argv)
		return (cd_home(data, 0));
	if (*(argv + 1))
		return (errmsg("minishell: cd: too many arguments\n", 0, 0, 1));
	if (!ft_strcmp(*argv, "~"))
		return (cd_home(data, 1));
	if (!**argv)
		return (0);
	if (!ft_strcmp(*argv, "-"))
		return (cd_oldpwd(data));
	if (chdir(*argv) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(*argv);
		return (errno);
	}
	free_str(&data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd)
		|| !var_set(&data->vars, "PWD", data->pwd))
		return (M_ERR);
	return (0);
}
