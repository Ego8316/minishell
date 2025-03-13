/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:27 by ego               #+#    #+#             */
/*   Updated: 2025/03/13 02:36:54 by ego              ###   ########.fr       */
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

static int	check_export_arg(char *arg)
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
	if (arg[i++] != '=')
		return (0);
	return (1);
}

/**
 * @brief Executes the export builtin: tries and put the given variable and
 * its value in the environment. If no argument given, prints all environment
 * variables with "declare -x " before.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return 0 on success, 1 otherwise.
 */
int	export_builtin(t_data *data, t_token *args)
{
	int	status;

	if (!args || args->type != TEXT)
		return (print_declare_env(data));
	status = 0;
	while (args && args->type == TEXT)
	{
		if (check_export_arg(args->str))
			env_add_line(data, args->str);
		else
			status = errmsg("minishell: export: `",
					args->str, "': not a valid identifier\n", 1);
		args = args->nxt;
	}
	return (status);
}
