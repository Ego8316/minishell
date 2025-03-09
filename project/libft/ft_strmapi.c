/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:20 by hcavet            #+#    #+#             */
/*   Updated: 2025/03/04 17:11:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Applies a function to each character in a string
 * and returns a new string.
 * 
 * @param s The string to modify.
 * @param f The function to apply to each character.
 * 
 * @return The modified string.
 */
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*strmapi;
	unsigned int	i;

	if (!s)
		return (NULL);
	strmapi = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!strmapi)
		return (NULL);
	i = 0;
	while (s[i])
	{
		strmapi[i] = f(i, s[i]);
		i++;
	}
	strmapi[i] = '\0';
	return (strmapi);
}
