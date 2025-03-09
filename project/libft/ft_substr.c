/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:53:34 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 20:19:32 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start + len)
	{
		if (s_len > start)
			len = s_len - start;
		else
			len = 0;
	}
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	ft_memcpy(sub, s + start, len);
	sub[len] = 0;
	return (sub);
}
