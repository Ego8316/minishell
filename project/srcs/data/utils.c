/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:16:52 by ego               #+#    #+#             */
/*   Updated: 2025/03/18 14:32:46 by ego              ###   ########.fr       */
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
 * @brief Computes the number of variables of all types.
 * 
 * @param vars Var list.
 * 
 * @return The number of elements in the list.
 */
int	get_vars_size(t_var *vars)
{
	t_var	*v;
	int		size;

	size = 0;
	v = vars;
	while (v)
	{
		size++;
		v = v->nxt;
	}
	return (size);
}
