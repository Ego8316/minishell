/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:07:11 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:04:46 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Concatenates two strings into one.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return The allocated concatenated string, NULL
 * if allocation fails or one of the two strings is NULL.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[i - len1])
	{
		join[i] = s2[i - len1];
		i++;
	}
	join[i] = '\0';
	return (join);
}
