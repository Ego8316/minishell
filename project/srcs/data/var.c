/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:45:35 by ego               #+#    #+#             */
/*   Updated: 2025/03/13 17:24:21 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Given a line of the form "VAR=value",
 * returns the identifier VAR's len. Identifier
 * validity has to be checked beforehand.
 * 
 * @param line Line to be parsed.
 * 
 * @return Identifier line.
 */
int	line_get_identifier_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '=')
		len++;
	return (len);
}

/**
 * @brief Given a line of the form "VAR=value",
 * returns the value. Identifier validity
 * has to be checked beforehand.
 * 
 * @param line Line to be parsed.
 * 
 * @return Allocated parsed value,
 * NULL if allocation fails.
 */
char	*line_get_value(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=')
		return (ft_strdup(line + i + 1));
	else
		return (ft_strdup(""));
}

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

	node = (t_var *)malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->identifier = ft_strndup(line, line_get_identifier_len(line));
	if (!node->identifier)
		return (free(node), NULL);
	node->value = line_get_value(line);
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
