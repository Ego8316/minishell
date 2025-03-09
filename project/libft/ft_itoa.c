/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:55:16 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 19:55:18 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function was made as challange to fit on least lines I could,
//Not to be easily readable.
//It's logic however is same as if it was made in nice syntax
char	*ft_itoa(int n)
{
	int		i;
	int		temp;
	char	*result;

	i = 1 + (n < 0);
	temp = n;
	while (temp > 9 || temp < -9)
		temp /= 10 + (0 * i++);
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (0);
	result[i--] = 0;
	result[i--] = (n % 10) * (((temp) >= 0) * 2 - 1) + '0';
	while (i >= (temp < 0))
		result[i--] = ((n /= 10) % 10) * (((temp) >= 0) * 2 - 1) + '0';
	result[0] = (temp < 0) * '-' + (temp >= 0) * result[0];
	return (result);
}
