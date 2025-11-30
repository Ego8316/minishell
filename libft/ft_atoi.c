/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:08:42 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:50:42 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Converts a string to an integer.
 * 
 * @param str The string to convert.
 * 
 * @return The integer value of the string.
 */
int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = -(nptr[i] - 44);
		i++;
	}
	if (sign < 0 && !ft_strcmp("2147483648", nptr + i))
		return (-2147483648);
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}
