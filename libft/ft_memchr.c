/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:55:58 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:33:56 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Locates the first occurrence of a character in a memory block.
 * 
 * @param b The memory block to search.
 * @param c The character to search for.
 * @param len The number of bytes to search.
 * 
 * @return A pointer to the first occurrence of the character,
 * NULL if not found.
 */
void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)b;
	i = -1;
	while (++i < len)
	{
		if (s[i] == (unsigned char)c)
			return (s + i);
	}
	return (NULL);
}
