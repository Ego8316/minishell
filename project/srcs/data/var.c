/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:45:35 by ego               #+#    #+#             */
/*   Updated: 2025/03/14 14:58:43 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates memory for a new var list node and add
 * it at the end of the given list. Takes as a parameter a
 * line in the form "VAR=value" and splits into identifier
 * and value. If the value or the equal sign is missing, 
 * puts an empty string as value by default. Identifier 
 * validity has to be checked beforehand. One must also
 * check if the var is not already in the list beforehand.
 * 
 * @param vars Pointer to the var list, in principle the first node.
 * @param line Line to be to be parsed.
 * @param type Var type.
 * 
 * @return 1 on success, 0 if allocation fails.
 */
int	var_add_line(t_var **vars, char *line, t_var_type type)
{
	t_var	*v;

	if (!vars)
		return (0);
	if (!*vars)
	{
		*vars = var_new_node(line, type);
		return (*vars != NULL);
	}
	v = var_new_node(line, type);
	if (!v)
		return (0);
	v->nxt = *vars;
	*vars = v;
	return (1);
}

/**
 * @brief Searches through the var list for a variable with
 * same identifier as provided with the line in the form
 * "VAR=value" and returns a pointer to that variable.
 * 
 * @param vars Pointer to the beginning of the var list.
 * @param line Line to be parsed.
 * 
 * @return Pointer to the variable if there is a match,
 * NULL otherwise.
 */
t_var	*var_get(t_var **vars, char *line)
{
	t_var	*v;

	if (!vars)
		return (NULL);
	v = *vars;
	while (v)
	{
		if (!ft_strncmp(v->identifier, line, line_get_identifier_len(line)))
			return (v);
		v = v->nxt;
	}
	return (NULL);
}

/**
 * @brief Sets a local variable given a line of the form "VAR=value".
 * If the var is not found in the var list, adds it to the list.
 * If the var is found, changes its value to the new one. If it is
 * marked, changes its type to ENV.
 * 
 * @param vars Pointer to the beginning of the var list.
 * @param line Line to be parsed.
 * 
 * @return 1 on success, 0 if allocation fails.
 */
int	var_set(t_var **vars, char *line)
{
	t_var	*v;

	v = var_get(vars, line);
	if (!v)
		return (var_add_line(vars, line, LOCAL));
	free_str(&v->value);
	v->value = line_get_value(line);
	if (!v->value)
		return (0);
	if (v->type == MARKED)
		v->type = ENV;
	return (1);
}
