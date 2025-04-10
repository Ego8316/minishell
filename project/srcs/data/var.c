/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:45:35 by ego               #+#    #+#             */
/*   Updated: 2025/04/10 19:08:23 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates memory for a new var list node.
 * Takes as parameters the identifier, value and type.
 * Identifier validity has to be checked beforehand.
 * 
 * @param identifier The identifier.
 * @param value The value.
 * @param type Var type.
 * 
 * @return The new allocated node, NULL if allocation fails.
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
 * @brief Searches through the var list for a variable with
 * same identifier as provided.
 * 
 * @param vars Pointer to the beginning of the var list.
 * @param identifier Identifier.
 * 
 * @return Pointer to the variable if there is a match,
 * NULL otherwise.
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
 * @brief Searches through the var list for a variable with
 * same identifier as provided. Allocates memory and returns
 * its value (an empty string if ID not found).
 * 
 * @param vars Pointer to the beginning of the var list.
 * @param identifier Variable's identifier.
 * 
 * @return Allocated copy of the value, NULL if allocation fails.
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
 * @brief Allocates memory for a new var list node and add
 * it at the end of the given list. Takes as a parameter an
 * identifier and its value. Identifier validity has to be
 * checked beforehand. One must also check if the var is not
 * already in the list beforehand.
 * 
 * @param vars Pointer to the var list, in principle the first node.
 * @param identifier The identifier.
 * @param value The value.
 * @param type Var type.
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
 * @brief Sets an environment variable given an identifier and
 * a value. If the var is not found in the var list, does nothing.
 * If the var is found, changes its value to the new one.
 * 
 * @param vars Pointer to the beginning of the var list.
 * @param identifier The identifier.
 * @param value The value.
 * 
 * @return 1 on success, 0 if allocation fails.
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
