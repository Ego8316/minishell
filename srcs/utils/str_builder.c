/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:31:47 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 14:02:48 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Concatenates two strings into a new allocation.
 *
 * Joins the existing builder string with the `end` string, freeing both inputs
 * and storing the result back in `str`.
 *
 * @param str Builder string pointer (may be NULL).
 * @param end String to append (may be NULL).
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
t_bool	strb_join(char **str, char *end)
{
	char	*new;
	int		strl;
	int		endl;

	strl = ft_strlen_null(*str);
	endl = ft_strlen_null(end);
	new = malloc(sizeof(char) * (strl + endl + 1));
	if (new)
	{
		new[strl + endl] = 0;
		if (*str)
			ft_memcpy(new, *str, sizeof(char) * strl);
		if (end)
			ft_memcpy(new + strl, end, sizeof(char) * endl);
	}
	if (*str)
		free(*str);
	if (end)
		free(end);
	if (new)
		*str = new;
	else
		*str = 0;
	return (new != 0);
}

/**
 * @brief Appends a single character to the builder string.
 *
 * Allocates a new buffer large enough for the existing content plus the new
 * character, frees the old buffer, and stores the result.
 *
 * @param str Builder string pointer (may be NULL).
 * @param end Character to append.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
t_bool	strb_append(char **str, char end)
{
	char	*new;
	int		strl;

	strl = ft_strlen_null(*str);
	new = malloc(sizeof(char) * (strl + 2));
	if (new)
	{
		new[strl + 1] = 0;
		new[strl] = end;
		if (*str)
			ft_memcpy(new, *str, sizeof(char) * strl);
	}
	if (*str)
		free(*str);
	if (new)
		*str = new;
	else
		*str = 0;
	return (new != 0);
}

/**
 * @brief Allocates an empty string builder.
 *
 * @return Newly allocated empty string, NULL on allocation failure.
 */
char	*strb_new(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (str)
		str[0] = 0;
	return (str);
}

/**
 * @brief Extracts a substring and stores it in an output pointer.
 *
 * Thin wrapper around `ft_substr` that standardizes the boolean return
 * convention used in the parser.
 *
 * @param str Source string.
 * @param start Start index.
 * @param count Number of characters to copy.
 * @param ret Output pointer for the allocated substring.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
t_bool	strb_sub(char *str, int start, int count, char **ret)
{
	*ret = 0;
	*ret = ft_substr(str, start, count);
	return (*ret != 0);
}
