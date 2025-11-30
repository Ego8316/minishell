/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:40:56 by hcavet            #+#    #+#             */
/*   Updated: 2025/03/04 17:02:08 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Moves a block of memory to another location safely.
 * 
 * @param dst The destination memory block.
 * @param src The source memory block.
 * @param len The number of bytes to move.
 * 
 * @return A pointer to the destination memory block.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	if (!dst && !src && len > 0)
		return (NULL);
	d = (unsigned char *)dst;
	if ((s < d) && (d < s + len))
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
