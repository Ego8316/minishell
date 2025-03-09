/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:15:25 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 15:08:16 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb * size > 4294967295UL)
		return (0);
	result = malloc(nmemb * size);
	if (!result)
		return (0);
	ft_bzero(result, nmemb * size);
	return (result);
}
