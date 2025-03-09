/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:03 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:33:23 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a duplicate of a string up to n characters.
 * 
 * @param s The string to duplicate.
 * @param n The maximum number of characters to duplicate.
 * 
 * @return The allocated duplicated string, NULL if allocation fails.
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*ndup;
	size_t	i;

	if (!n)
		return (NULL);
	ndup = (char *)malloc((n + 1) * sizeof(char));
	if (!ndup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		ndup[i] = s[i];
		i++;
	}
	ndup[i] = '\0';
	return (ndup);
}
