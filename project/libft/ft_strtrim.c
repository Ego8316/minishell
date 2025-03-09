/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:53:48 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 20:58:50 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static char	*ft_getstr(char const *s1, char const *set, int *start, int *end)
{
	int	i;

	i = 0;
	while (s1[i] && ft_isinset(s1[i], set))
		i++;
	*start = i;
	while (s1[i])
		i++;
	while (i >= *start && (!s1[i] || ft_isinset(s1[i], set)))
		i--;
	*end = i + 1;
	return (malloc((*end - *start + 1) * sizeof(char)));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (0);
	result = ft_getstr(s1, set, &start, &end);
	if (!result)
		return (0);
	ft_memcpy(result, s1 + start, end - start + 1);
	result[end - start] = 0;
	return (result);
}
