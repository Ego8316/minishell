/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:20:41 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:40:52 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Compares two strings lexicographically.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return 0 if the strings are equal, a positive value if s1 > s2,
 * or a negative value if s1 < s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int		diff;
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff)
			return (diff);
		i++;
	}
	return (0);
}
