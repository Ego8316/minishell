/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:27:14 by ego               #+#    #+#             */
/*   Updated: 2025/04/09 22:47:53 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Gets the start index of the trimmed string from the original string.
 * 
 * @param s The original string.
 * @param set The set of characters to be removed.
 * 
 * @return The start index.
 */
static size_t	ft_strtrim_get_start(const char *s, const char *set)
{
	size_t	start;

	start = 0;
	while (ft_char_in_str(s[start], set) != -1)
		start++;
	return (start);
}

/**
 * @brief Gets the end index of the trimmed string from the original string.
 * 
 * @param s The original string.
 * @param set The set of characters to be removed.
 * @param start The start index.
 * 
 * @return The end index.
 */
static size_t	ft_strtrim_get_end(const char *s, const char *set, size_t start)
{
	size_t	end;

	if (ft_strlen(s) == 0)
		return (0);
	end = ft_strlen(s) - 1;
	while (start < end && ft_char_in_str(s[end], set) != -1)
		end--;
	return (end);
}

/** 
 * @brief Allocates memory and returns a copy of s with characters from
 * set removed from the beginning and the end.
 * 
 * @param s The string to be trimmed.
 * @param set The string containing the set of characters to be removed.
 * 
 * @return The allocated trimmed string, NULL if allocation fails.
 */
char	*ft_strtrim(const char *s, const char *set)
{
	char	*trim;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	if (!set || !(*s) || !(*set))
		return (ft_strdup(s));
	start = ft_strtrim_get_start(s, set);
	end = ft_strtrim_get_end(s, set, start);
	trim = (char *)malloc((end - start + 2) * sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (i < end - start + 1)
	{
		trim[i] = s[start + i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
