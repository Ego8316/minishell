/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:45:35 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:42:13 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates memory for a new variable list node. Given the identifier,
 * value, and type, this function creates a new node.
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param identifier Identifier of the variable.
 * @param value Value associated with the variable.
 * @param type Type of the variable (either `LOCAL`, `MARKED` or `ENV`).
 * 
 * @return Newly allocated node, NULL if allocation fails.
 */
static t_var	*var_new_node(char *identifier, char *value, t_var_type type)
{
	t_var	*node;

	node = (t_var *)malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->identifier = ft_strdup(identifier);
	if (!node->identifier)
		return (free(node), NULL);
	node->value = ft_strdup(value);
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
 * @brief Searches the variable list for a variable with the same identifier as
 * provided.
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param vars Pointer to the beginning of the variable list.
 * @param identifier Identifier to search for.
 * 
 * @return Pointer to the variable with the matching identifier, NULL if no
 * match is found.
 */
t_var	*var_get(t_var **vars, char *identifier)
{
	t_var	*v;

	if (!vars)
		return (NULL);
	v = *vars;
	while (v)
	{
		if (!ft_strcmp(v->identifier, identifier))
			return (v);
		v = v->nxt;
	}
	return (NULL);
}

/**
 * @brief Searches the variable list for a variable with the same identifier
 * as provided. Allocates memory and returns a copy of the value of the
 * variable, or a copy of the empty string if not found.
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param vars Pointer to the beginning of the variable list.
 * @param identifier Identifier of the variable to look for.
 * 
 * @return Allocated copy of the value, allocated copy of the empty string if
 * the identifier is not found, NULL if allocation fails.
 */
char	*var_get_value(t_var *vars, char *identifier)
{
	t_var	*v;

	v = var_get(&vars, identifier);
	if (!v)
		return (ft_strdup(""));
	else
		return (ft_strdup(v->value));
}

/**
 * @brief Given an identifier, value and type, allocates memory for a new
 * variable list node and adds it at the end of the provided variable list.
 * 
 * @warning The validity of the identifier must be checked beforehand, and
 * the variable should not already be in the list.
 * 
 * @param vars Pointer to the variable list, in principle the first node.
 * @param identifier Identifier of the variable.
 * @param value Value associated with the variable.
 * @param type Type of the variable (either `LOCAL`, `MARKED` or `ENV`).
 * 
 * @return 1 on success, 0 if allocation fails.
 */
int	var_add(t_var **vars, char *identifier, char *value, t_var_type type)
{
	t_var	*v;

	if (!vars)
		return (0);
	if (!*vars)
	{
		*vars = var_new_node(identifier, value, type);
		return (*vars != NULL);
	}
	v = *vars;
	while (v->nxt)
		v = v->nxt;
	v->nxt = var_new_node(identifier, value, type);
	if (!v->nxt)
		return (0);
	return (1);
}

/**
 * @brief Given an identifier and a value, sets a variable's value. If the
 * variable is not found in the variable list, it is added as an environment
 * variable (type `ENV`) with the provided value. If it is found, frees the
 * previous value and updates it to the new one.
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param vars Pointer to the beginning of the variable list.
 * @param identifier Identifier of the variable.
 * @param value New value to be set.
 * 
 * @return 1 if the operation is successful, 0 if memory allocation fails.
 */
int	var_set(t_var **vars, char *identifier, char *value)
{
	t_var	*v;

	v = var_get(vars, identifier);
	if (!v)
		return (var_add(vars, identifier, value, ENV));
	free_str(&v->value);
	v->value = ft_strdup(value);
	if (!v->value)
		return (0);
	return (1);
}
