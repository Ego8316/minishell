/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:56:35 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:35:16 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Compares two strings lexicographically
 * up to a specified number of characters.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The maximum number of characters to compare.
 * 
 * @return 0 if the strings are equal, a positive value if s1 > s2,
 * or a negative value if s1 < s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff)
			return (diff);
		i++;
	}
	return (0);
}
