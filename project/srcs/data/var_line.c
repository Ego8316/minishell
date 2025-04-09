/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:29:36 by ego               #+#    #+#             */
/*   Updated: 2025/04/09 14:26:01 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates memory for a new var list node.
 * Takes as a parameter a line in the form "VAR=value"
 * and splits into identifier and value. If the value
 * or the equal sign is missing, puts an empty string
 * as value by default. Identifier validity has to
 * be checked beforehand.
 * 
 * @param line Line to be parsed.
 * @param type Var type.
 * 
 * @return The new allocated node, NULL if allocation fails.
 */
t_var	*var_new_node_line(char *line, t_var_type type)
{
	t_var	*node;

	node = (t_var *)malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->identifier = ft_strndup(line, line_get_identifier_len(line));
	if (!node->identifier)
		return (free(node), NULL);
	node->value = line_get_value(line);
	if (!node->value)
	{
		free(node->identifier);
		free(node);
		return (NULL);
	}
	node->type = type;
	node->nxt = NULL;
	return (node);
}

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
		*vars = var_new_node_line(line, type);
		return (*vars != NULL);
	}
	v = *vars;
	while (v->nxt)
		v = v->nxt;
	v->nxt = var_new_node_line(line, type);
	if (!v->nxt)
		return (0);
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
t_var	*var_get_line(t_var **vars, char *line)
{
	t_var	*v;
	int		id_len;

	if (!vars)
		return (NULL);
	v = *vars;
	while (v)
	{
		id_len = line_get_identifier_len(line);
		if (!ft_strncmp(v->identifier, line, id_len) && !v->identifier[id_len])
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
int	var_set_line(t_var **vars, char *line)
{
	t_var	*v;

	v = var_get_line(vars, line);
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

/**
 * @brief Checks if the given string is a valid indentifier.
 * A valid identifier should not be empty, should start only
 * by an alphabetic character or an underscore.
 * 
 * @param arg The string to be checked.
 * 
 * @return 1 if it is a valid identifier, 0 otherwise.
 */
int	is_valid_identifier(char *arg)
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
