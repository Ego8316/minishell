/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stristype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:26:16 by ego               #+#    #+#             */
/*   Updated: 2025/04/09 23:02:40 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a string is only made of one given type.
 * 
 * @param s String to be checked.
 * @param f Function used to check the type (isspace for example).
 * 
 * @return 1 if it is only made of the given type, 0 otherwise.
 */
int	ft_stristype(char *s, int (*f)(int))
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!f(s[i]))
			return (0);
		i++;
	}
	return (1);
}
