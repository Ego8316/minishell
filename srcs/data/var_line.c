/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:29:36 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:42:19 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates memory for a new variable list node. Given a line in the
 * form "VAR=value", it splits the line into identifier and value. If the value
 * or '=' is missing, an empty string is used as the value by default.
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param line Line to be parsed.
 * @param type Type of the variable.
 * 
 * @return Pointer to the new allocated node, NULL if allocation fails.
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
 * @brief Allocates memory for a new variable list node and adds it to the end
 * of the given list. Given a line in the form "VAR=value", it splits into
 * identifier and value. If the value or '=' is missing, an empty string is
 * used as the value by default.
 * 
 * @warning The validity of the identifier must be checked beforehand, and
 * the variable should not already be in the list.
 * 
 * @param vars Pointer to the variable list, in principle the first node.
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
 * @brief Searches through the variable list for a variable with the same
 * identifier as the one provided in the form "VAR=value" and returns a
 * pointer to that variable.
 * 
 * @param vars Pointer to the beginning of the variable list.
 * @param line Line to be parsed.
 * 
 * @return Pointer to the variable if there is a match, NULL otherwise.
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
 * @brief Sets a local variable given a line of the form "VAR=value". If the
 * variable is not found in the list, it is added. If it is found, its value is
 * updated. If the variable has type `MARKED`, its type is changed to `ENV`.
 * 
 * @param vars Pointer to the beginning of the variable list.
 * @param line Line to be parsed.
 * 
 * @return 1 if the operation is successful, 0 if memory allocation fails.
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
