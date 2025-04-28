/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:48:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	record_wildcard(int i, int **wcs)
{
	int	*new;
	int	len;

	len = 0;
	while (*wcs && (*wcs)[len] != -1)
		len++;
	new = malloc((len + 2) * sizeof(int));
	if (!new)
	{
		if (*wcs)
			free(*wcs);
		return (FALSE);
	}
	new[len + 1] = -1;
	new[len] = i;
	while (len-- > 0)
		new[len] = (*wcs)[len];
	if (*wcs)
		free(*wcs);
	*wcs = new;
	return (TRUE);
}

t_bool	record_wildcards(char *str, int **wcs, int offset)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && !record_wildcard(i + offset, wcs))
		{
			free(str);
			if (*wcs != 0)
				free(*wcs);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
