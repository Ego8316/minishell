/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:30:14 by ego               #+#    #+#             */
/*   Updated: 2025/04/09 22:06:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Goes through the string s to search for
 * the first occurence of the character c. If found,
 * returns the position, -1 otherwise.
 * 
 * @param c Character to find.
 * @param s String to be searched.
 * 
 * @return Position of the character, -1 otherwise.
 */
int	ft_char_in_str(char c, const char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
