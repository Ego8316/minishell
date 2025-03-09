/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:15:25 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/01 19:17:38 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	cmp_i;

	i = 0;
	cmp_i = 0;
	while (1)
	{
		if (!little[cmp_i])
			return ((char *)big + i);
		if (i + cmp_i >= len || !big[i + cmp_i])
			break ;
		if (big[i + cmp_i] != little[cmp_i])
		{
			cmp_i = 0;
			i++;
		}
		else
			cmp_i++;
	}
	return (0);
}
