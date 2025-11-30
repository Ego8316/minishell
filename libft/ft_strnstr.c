/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:26:54 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:00:07 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Locates the first occurrence of the substring needle in
 * the string haystack up to len characters.
 * 
 * @param haystack The string to search in.
 * @param needle The substring to search for.
 * @param len The maximum number of characters of needle to search for.
 * 
 * @return A pointer to the first occurrence of the substring,
 * NULL if not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j] && haystack[i] && i < len)
		{
			i++;
			j++;
		}
		if (!needle[j])
			return ((char *)(haystack + i - j));
		i += 1 - j;
	}
	return (NULL);
}
