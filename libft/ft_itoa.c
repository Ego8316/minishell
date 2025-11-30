/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:27:52 by hcavet            #+#    #+#             */
/*   Updated: 2025/03/04 17:28:46 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Computes the result of a to the power n.
 * 
 * @param a Exponential base.
 * @param n Exponent.
 * 
 * @return The result of a to the power n.
 */
static int	ft_power(int a, int n)
{
	if (n < 0)
		return (0);
	if (n > 0)
		return (a * ft_power(a, n - 1));
	return (1);
}

/**
 * @brief Computes the number of digits of the integer n.
 * 
 * @param n The integer n.
 * 
 * @return The number of digits.
 */
static int	ft_itoa_count_digits(int n)
{
	int	digits;

	if (!n)
		return (1);
	digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/**
 * @brief Gives a string representing the integer received as an argument.
 * Handles negative numbers.
 * 
 * @param n Number to be converted.
 * 
 * @return The allocated converted string, NULL if allocation fails.
 */
char	*ft_itoa(int n)
{
	char	*nptr;
	int		digits;
	int		i;

	digits = ft_itoa_count_digits(n);
	nptr = (char *)malloc((digits + (n < 0) + 1) * sizeof(char));
	if (!nptr)
		return (NULL);
	if (n < 0)
		nptr[0] = '-';
	i = n < 0;
	while (digits > 0)
	{
		nptr[i] = '0' + n / ((1 - 2 * (n < 0)) * ft_power(10, digits - 1));
		n %= (1 - 2 * (n < 0)) * ft_power(10, digits - 1);
		i++;
		digits--;
	}
	nptr[i] = '\0';
	return (nptr);
}
