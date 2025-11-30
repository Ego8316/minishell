/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:34:47 by hcavet            #+#    #+#             */
/*   Updated: 2025/03/04 17:03:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Sets a block of memory to zero.
 * 
 * @param s The memory block to set to zero.
 * @param n The number of bytes to set.
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
