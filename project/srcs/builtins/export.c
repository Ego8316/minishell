/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:27 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 14:09:15 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all exported environment variables in the format `declare -x 
 * VAR="value"` for each environment variable. If a variable is marked (but not
 * set), only prints `declare -x VAR`.
 * 
 * @param data Pointer to the main data structure.
 * 
 * @return Exit status: 0 for success.
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
 * @brief Handles a variable assignment or update. Supports eight different
 * cases depending on the current state of the variable (`NULL`, `LOCAL`,
 * `MARKED`, `ENV`). Either adds the variable to the list or updates its
 * value and type as needed.
 * @brief - If `var` is `NULL` and there is a '=', adds a new var to the list
 * with type `ENV`.
 * @brief - If `var` is `NULL` and there is no '=', adds a new var to the list
 *  with type `MARKED`.
 * @brief - If `var` has type `LOCAL` and there is no '=', changes its type to
 *  `ENV`.
 * @brief - If `var` has type `LOCAL` and there is a '=', updates its value and
 *  its type to `ENV`.
 * @brief - If `var` has type `MARKED` and there is no '=', changes its type to
 *  `ENV`.
 * @brief - If `var` has type `MARKED` and there is a '=', updates its value
 * and changes its type to ENV.
 * @brief - If `var` has type `ENV` and there is a '=', does nothing.
 * @brief - If `var` has type `ENV` and there is no '=', updates its value.
 * 
 * @param data Pointer to the main data structure.
 * @param var Pointer to the variable to be handled.
 * @param line Line to be parsed.
 * 
 * @return 1 is the operation is successful, 0 if memory allocation fails.
 */
static int	handle_var(t_data *data, t_var *var, char *line)
{
	int		eq;
	int		ret;

	eq = ft_char_in_str('=', line) != -1;
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
 * @brief Executes the `export` builtin command: adds or updates environment
 * variables. If no arguments are provided, it prints all exported environment
 * variables in the format `declare -x VAR="value"`.
 * 
 * @note If an argument does not represent a valid identifier, prints an error
 * message to the standard error and the function returns 1.
 * 
 * @param data Pointer to the main data structure.
 * @param argv Arguments.
 * 
 * @return Exit status: 0 on success, 1 if an argument does not represent a
 * valid identifier, `M_ERR` if memory allocation fails.
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
