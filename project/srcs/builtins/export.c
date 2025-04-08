/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:27 by ego               #+#    #+#             */
/*   Updated: 2025/04/07 19:08:41 by ego              ###   ########.fr       */
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
			printf("declare -x %s=\"%s\"\n", v->identifier, v->value);
		v = v->nxt;
	}
	return (0);
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
 * @param argv Arguments.
 * 
 * @return 0 on success, 1 otherwise, -2 if allocation fails.
 */
int	export_builtin(t_data *data, char **argv)
{
	int		status;
	t_var	*var;

	if (!*argv)
		return (print_declare_env(data));
	status = 0;
	while (*argv)
	{
		if (!is_valid_identifier(*argv))
			status = errmsg("minishell: export: `",
					*argv, "': not a valid identifier\n", 1);
		else
		{
			var = var_get_line(&data->vars, *argv);
			if (!handle_var(data, var, *argv))
				return (M_ERR);
		}
		argv++;
	}
	return (status);
}
