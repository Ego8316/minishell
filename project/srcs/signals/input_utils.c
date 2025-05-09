/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:48:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_append_free(char *str, char c)
{
	char	*new;
	size_t	str_len;

	str_len = ft_strlen_null(str);
	new = malloc((str_len + 2) * sizeof(char));
	if (new)
	{
		new[str_len + 1] = 0;
		new[str_len] = c;
		ft_memcpy(new, str, str_len);
	}
	free(str);
	return (new);
}

char	*str_remove_free(char *str, size_t count)
{
	char	*new;
	size_t	str_len;

	str_len = ft_strlen_null(str);
	if (count > str_len)
		count = str_len;
	count = str_len - count;
	new = malloc((count + 1) * sizeof(char));
	if (new)
	{
		new[count] = 0;
		ft_memcpy(new, str, count);
	}
	free(str);
	return (new);
}
