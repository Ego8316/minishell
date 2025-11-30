/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:18:45 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:26:07 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Computes the length needed for the substring.
 * 
 * @param s The string to extract from.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * 
 * @return The length of the extracted substring.
 */
static size_t	ft_substr_len(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (0);
	if (s_len - start < len)
		return (s_len - start);
	return (len);
}

/** 
 * @brief Extracts a substring from a string. The substring starts
 * at index start and has a maximum length of len.
 * 
 * @param s The string to extract from.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * 
 * @return The allocated extracted substring.
 */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	sub_len;

	if (!s)
		return (NULL);
	sub_len = ft_substr_len(s, start, len);
	sub = (char *)malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < sub_len)
		sub[i] = s[i + start];
	sub[i] = '\0';
	return (sub);
}
