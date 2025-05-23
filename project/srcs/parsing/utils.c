/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:29:33 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/23 16:52:05 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_char_oper(char c)
{
	return (c == '|' || c == '&' || c == '>'
		|| c == '<' || c == '(' || c == ')');
}

t_bool	syntax_error(t_parse_data *data, int i)
{
	g_last_exit_code = errmsg("minishell: syntax error near unexpected token `",
			&data->cmd[i], "'\n", 2);
	printf("in command: '%s'\n", data->cmd);
	i += 13;
	while (i-- > 0)
		printf("%c", '-');
	printf("^\n");
	return (FALSE);
}

/**
 * @brief Checks if a given position in the pattern corresponds to an actual
 * wildcard (i.e. not escaped).
 * 
 * @param pos Current index in the pattern being checked.
 * @param arr Array of wildcard positions that are NOT escaped. This array is
 * expected to be terminated with -1.
 * 
 * @return 1 if the '*' at this position is not escaped and is a valid
 * wildcard, 0 otherwise.
 */
static int	is_not_escaped_wildcard(int pos, int *arr)
{
	int	i;

	i = 0;
	while (arr[i] != -1)
	{
		if (arr[i] == pos)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Matches a filename or string against a simplified pattern, supporting
 * only the '*' wildcard. Escaped wildcards (i.e. literal asteriks) are handled
 * via an array of valid wildcard positions obtained during lexicalization.
 * 
 * @param pattern Pattern to match.
 * @param name The string to match against the pattern.
 * @param pos Current position in the pattern (to check against escaped '*').
 * @param arr Array of wildcard positions that are NOT escaped. This array is
 * expected to be terminated with -1.
 * 
 * @return 0 if the name matches the pattern, 1 otherwise.
 * 
 * @note Only '*' wildcards are supported.
 */
int	ft_fnmatch(const char *pattern, const char *name, int pos, int *arr)
{
	if (!*pattern)
		return (*name != '\0');
	if (*pattern == *name)
		return (ft_fnmatch(pattern + 1, name + 1, pos + 1, arr));
	if (*pattern == '*' && is_not_escaped_wildcard(pos, arr))
	{
		if (ft_fnmatch(pattern + 1, name, pos + 1, arr) == 0)
			return (0);
		if (*name && ft_fnmatch(pattern, name + 1, pos, arr) == 0)
			return (0);
		return (1);
	}
	return (1);
}

/**
 * @brief Cleans the matches token list. If the list has more than one node,
 * removes the first and sorts all the others.
 * 
 * @param head Head of the token list to be sorted.
 * 
 * @warning This function should only be used on a token list made only of
 * TEXT types.
 * 
 * @return Pointer to the tail of the list.
 */
t_token	*clean_matches(t_token **head)
{
	t_token	*t;
	int		swapped;

	swapped = 1;
	if ((*head)->nxt)
	{
		t = *head;
		*head = (*head)->nxt;
		token_free_node(t);
	}
	while (swapped)
	{
		swapped = 0;
		t = *head;
		while (t && t->nxt)
		{
			if (ft_strcmp(t->str, t->nxt->str) > 0)
			{
				swap_str(&t->str, &t->nxt->str);
				swapped = 1;
			}
			t = t->nxt;
		}
	}
	return (t);
}
