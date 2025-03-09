/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:15:25 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 14:35:08 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	neg_multi;
	int	i;
	int	result;

	i = 0;
	while (ft_iswhitespace(nptr[i]))
		i++;
	neg_multi = 1;
	if (nptr[i] == '-')
		neg_multi *= -1 + (0 * i++);
	else if (nptr[i] == '+')
		i++;
	result = 0;
	while (ft_isdigit(nptr[i]))
		result = (result * 10) + ((nptr[i++] - '0') * neg_multi);
	return (result);
}
