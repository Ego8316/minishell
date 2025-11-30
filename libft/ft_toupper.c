/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:24:07 by hcavet            #+#    #+#             */
/*   Updated: 2025/03/04 17:07:48 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Converts a character to uppercase.
 * 
 * @param c The character to convert.
 * 
 * @return The uppercase equivalent of the character,
 * or the character itself if it's not lowercase.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c + 'A' - 'a');
	else
		return (c);
}
