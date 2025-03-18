/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:27 by ego               #+#    #+#             */
/*   Updated: 2025/03/18 14:43:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Simply prints all exported variables in declare -x VAR="val" format.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return 0 for success.
 */
static int	print_declare_env(t_data *data)
{
	t_var	*v;

	v = data->vars;
	while (v)
	{
		if (v->type == MARKED)
			printf("declare -x %s\n", v->identifier);
		if (v->type == ENV)
			printf("declare -x %s=%s\n", v->identifier, v->value);
		v = v->nxt;
	}
	return (0);
}

/**
 * @brief Checks if the given string is a valid indentifier.
 * A valid identifier should not be empty, should start only
 * by an alphabetic character or an underscore.
 */
static int	check_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Handles the var with a line of the form "VAR=value". Eight cases:
 * 
 * - If var (var is NULL) is not set:
 *  - If there is an equal sign (=), adds it to the var list with type ENV.
 *  - If there is no equal sign, adds it to the var list with type MARKED.
 * 
 * - If var is set locally (LOCAL type):
 *  - If there is no equal sign, changes its type to ENV.
 *  - If there is an equal sign, updates its value and changes its type to ENV.
 * 
 * - If var is already marked (MARKED type):
 *  - If there is no equal sign, changes its type to ENV.
 *  - If there is an equal sign, updates its value and changes its type to ENV.
 * 
 * - If var is already in the environment (ENV type):
 *  - If there is no equal sign, does nothing.
 *  - If there is an equal sign, updates its value in the var list.
 * 
 * @param data Pointer to the data structure.
 * @param var Pointer to the var to be handled.
 * @param line Line to parse.
 */
static int	handle_var(t_data *data, t_var *var, char *line)
{
	t_bool	eq;
	int		ret;

	eq = (t_bool)(ft_strchr(line, '=') != NULL);
	ret = 1;
	if (!var)
		ret = var_add_line(&data->vars, line, eq * ENV + (1 - eq) * MARKED);
	else if (var->type < ENV && !eq)
		var->type = ENV;
	else if (var && eq)
	{
		free_str(&var->value);
		var->value = line_get_value(line);
		if (!var->value)
			ret = 0;
		var->type = ENV;
	}
	return (ret);
}

/**
 * @brief Executes the export builtin: tries and put the given variable and
 * its value in the environment. If no argument given, prints all environment
 * variables with "declare -x " before.
 * 
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return 0 on success, 1 otherwise.
 */
int	export_builtin(t_data *data, t_token *args)
{
	int		status;
	t_var	*var;

	if (!args || args->type != TEXT)
		return (print_declare_env(data));
	status = 0;
	while (args && args->type == TEXT)
	{
		if (!check_valid_identifier(args->str))
			status = errmsg("minishell: export: `",
					args->str, "': not a valid identifier\n", 1);
		else
		{
			var = var_get_line(&data->vars, args->str);
			if (!handle_var(data, var, args->str))
				clean_exit(data, errmsg("malloc: failed allocation", 0, 0, 1));
		}
		args = args->nxt;
	}
	return (status);
}
