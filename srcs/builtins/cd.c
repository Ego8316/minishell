/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:35:52 by ego               #+#    #+#             */
/*   Updated: 2025/05/25 21:00:55 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Attempts to recover the home directory path.
 * 
 * First checks if the HOME environment variable is set. If not, attempts to
 * reconstruct a plausible home path using the USER variable. If neither is
 * available, defaults to "/home".
 * 
 * @return A newly allocated string containing the home path, NULL if memory
 * allocation fails.
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
 * @brief Changes to the user's home directory when HOME is unset.
 *
 * Attempts to construct a fallback home directory path when the HOME
 * variable is not available. Uses the USER variable to build a default
 * path (e.g. "/home/user"), or falls back to "/home" if USER is also
 * unset. Updates PWD and OLDPWD accordingly.
 *
 * @param data Pointer to the main data structure.
 *
 * @return Exit status: 0 on success, `M_ERR` on memory allocation failure.
 *
 * @note Should be used only when the directory argument is "~".
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
		return (free_str(&home), 1);
	}
	free_str(&home);
	free_str(&data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd, ENV)
		|| !var_set(&data->vars, "PWD", data->pwd, ENV))
		return (M_ERR);
	return (0);
}

/**
 * @brief Changes to the home directory using the HOME environment variable.
 *
 * If the HOME variable is unset and `fallback` is true, attempts to recover
 * the home path. If HOME is set but empty, does nothing.  Updates PWD and
 * OLDPWD accordingly.
 *
 * @param data Pointer to the main data structure.
 * @param fallback Enables fallback procedure when HOME is unset.
 *
 * @return Exit status: 0 on success, `M_ERR` on memory allocation failure.
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
		return (1);
	}
	free_str(&data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd, ENV)
		|| !var_set(&data->vars, "PWD", data->pwd, ENV))
		return (M_ERR);
	return (0);
}

/**
 * @brief Changes to the previous working directory (OLDPWD).
 * 
 * If OLDPWD is not set, prints an error on the standard error. If it is set
 * and valid, changes to that directory, updates internal variables, and prints
 * the new working directory on the standard output.  Updates PWD and OLDPWD
 * accordingly.
 * 
 * @param data Pointer to the main data structure.
 * 
 * @return Exit status: 0 on success, 1 on error, `M_ERR` on memory allocation
 * failure.
 */
static int	cd_oldpwd(t_data *data)
{
	t_var	*oldpwd;

	oldpwd = var_get(&data->vars, "OLDPWD");
	if (!oldpwd)
		return (errmsg("minishell: cd: OLDPWD not set\n", 0, 0, 1));
	if (!*oldpwd->value)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		if (!var_set(&data->vars, "OLDPWD", data->pwd, ENV))
			return (M_ERR);
		return (0);
	}
	if (chdir(oldpwd->value) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(oldpwd->value);
		return (1);
	}
	swap_str(&data->oldpwd, &data->pwd);
	if (!var_set(&data->vars, "OLDPWD", data->oldpwd, ENV)
		|| !var_set(&data->vars, "PWD", data->pwd, ENV))
		return (M_ERR);
	ft_putendl_fd(data->pwd, STDOUT_FILENO);
	return (0);
}

/**
 * @brief Executes the `cd` builtin command: changes current working directory
 * to the one provided.
 * 
 * Handles the following cases:
 * @brief - No argument: changes to $HOME.
 * @brief - "~": changes to $HOME and falls back if $HOME is unset.
 * @brief - "-": switches to OLDPWD and prints the new path.
 * @brief - Empty argument: does nothing.
 * @brief - Any other argument: attempts to change to that path.
 *
 * Also handles errors for unset HOME/OLDPWD or too many arguments.
 *
 * On success, updates the internal variables (PWD and OLDPWD) and the data
 * variables `pwd` and `oldpwd`.
 *
 * @param data Pointer to the data structure.
 * @param argv Arguments passed to the builtin.
 *
 * @return Exit status: 0 on success, 1 on error, `M_ERR` on memory allocation
 * failure.
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
		return (1);
	}
	free_str(&data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(0, 0);
	if (!data->pwd || !var_set(&data->vars, "OLDPWD", data->oldpwd, ENV)
		|| !var_set(&data->vars, "PWD", data->pwd, ENV))
		return (M_ERR);
	return (0);
}
