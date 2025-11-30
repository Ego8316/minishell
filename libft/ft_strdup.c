/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:58:02 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:19:18 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Creates a duplicate of a string.
 * 
 * @param s The string to duplicate.
 * 
 * @return The allocated duplicated string, NULL if allocation fails.
 */
char	*ft_strdup(const char *str)
{
	char	*cpy;
	size_t	i;

	cpy = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
