/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:12:56 by hcavet            #+#    #+#             */
/*   Updated: 2025/03/04 17:48:46 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Returns the length of a string.
 * 
 * @param s The string to measure.
 * 
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/** 
 * @brief Returns the length of a string and handles NULL string.
 * 
 * @param s The string to measure.
 * 
 * @return The length of the string, 0 is the string is NULL.
 */
size_t	ft_strlen_null(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}
