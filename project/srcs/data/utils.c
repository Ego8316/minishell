/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:16:52 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 02:46:16 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Given a line of the form "VAR=value", returns the length of the
 * identifier (VAR).
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param line Line to be parsed.
 * 
 * @return Length of the identifier in the line.
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
 * @brief Given a line of the form "VAR=value", returns the value associated
 * with the identifier.
 * 
 * @warning The validity of the identifier must be checked beforehand.
 * 
 * @param line Line to be parsed.
 * 
 * @return Allocated string representing the value, NULL if memory allocation
 * fails.
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
 * @brief Computes the number of variables of all types in the variable list.
 * 
 * @param vars Pointer to the variable list.
 * 
 * @return The total number of variables in the list.
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

/**
 * @brief Swaps the values of two string pointers.
 * 
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 */
void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}
