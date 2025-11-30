/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:08:34 by ego               #+#    #+#             */
/*   Updated: 2025/03/14 14:09:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and returns a new string, which is the
 * result of the concatenation of s1, s2 and s3.
 * 
 * @param s1 First string.
 * @param s2 Second string.
 * @param s3 Third string.
 * 
 * @return The new string. NULL if allocation fails.
 */
char	*join_strs(char *s1, char *s2, char *s3)
{
	char	*join;
	int		len1;
	int		len2;
	int		len3;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	join = (char *)malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < len1 && s1)
		join[i] = s1[i];
	i = -1;
	while (++i < len2 && s2)
		join[i + len1] = s2[i];
	i = -1;
	while (++i < len3 && s3)
		join[i + len1 + len2] = s3[i];
	join[i + len1 + len2] = 0;
	return (join);
}
