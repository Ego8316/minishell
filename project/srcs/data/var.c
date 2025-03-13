/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:45:35 by ego               #+#    #+#             */
/*   Updated: 2025/03/13 03:04:48 by ego              ###   ########.fr       */
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
 * @param line Line from envp to be split.
 * @param type Var type.
 * 
 * @return The new allocated node, NULL if allocation fails.
 */
t_var	*var_new_node(char *line, t_var_type type)
{
	t_var	*node;
	int		i;

	node = (t_var *)malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	node->identifier = ft_strndup(line, i);
	if (!node->identifier)
		return (free(node), NULL);
	if (line[i] == '=')
		node->value = ft_strdup(line + i + 1);
	else
		node->value = ft_strdup("");
	if (!node->value)
	{
		free(node);
		free(node->identifier);
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
 * validity has to be checked beforehand.
 * 
 * @param vars Pointer to the var list, in principle the first node.
 * @param line Line to be to be split.
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
	v = *vars;
	while (v->nxt)
		v = v->nxt;
	v->nxt = var_new_node(line, type);
	if (!v->nxt)
		return (0);
	return (1);
}
