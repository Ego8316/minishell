/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:55:01 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 19:55:05 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		divider;
	char	temp;

	divider = 1000000000;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	while ((n >= 0 && divider > n) || (n < 0 && - divider < n))
		divider /= 10;
	while (divider > 0)
	{
		temp = (n / divider) * ((n >= 0) * 2 - 1) + '0';
		ft_putchar_fd(temp, fd);
		n = n % divider;
		divider /= 10;
	}
}
