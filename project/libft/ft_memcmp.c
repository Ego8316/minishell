/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:19:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 16:57:43 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Compares two memory blocks byte by byte.
 * 
 * @param b1 A pointer to the first memory block.
 * @param b2 A pointer to the second memory block.
 * @param n The number of bytes to compare.
 * 
 * @return 0 if both memory blocks are equal, a non-zero 
 * value indicating the difference otherwise.
 */
int	ft_memcmp(const void *b1, const void *b2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	int				diff;
	size_t			i;

	s1 = (unsigned char *)b1;
	s2 = (unsigned char *)b2;
	i = 0;
	while (i < n)
	{
		diff = (int)s1[i] - (int)s2[i];
		if (diff)
			return ((int)diff);
		i++;
	}
	return (0);
}
