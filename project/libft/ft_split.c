/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:54:53 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/04 21:53:26 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_split_free_mem(char **list, size_t j)
{
	if (*list)
	{
		while (1)
		{
			j--;
			free(list[j]);
			if (j == 0)
				break ;
		}
	}
	free(list);
}

static int	ft_tryadd(char *start, unsigned int len, char **arr, size_t j)
{
	arr[j] = ft_substr(start, 0, len);
	if (arr[j])
		return (1);
	ft_split_free_mem(arr, j);
	return (0);
}

static char	**ft_fill_array(char const *s, char c, char **arr)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (1)
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		else if ((s[i] == c || s[i] == 0) && i > 0 && s[i - 1] != c)
		{
			if (!ft_tryadd((char *)s + start, (unsigned int)
					(i - start), arr, j))
				return (0);
			j++;
		}
		if (!s[i++])
			break ;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	counter;
	char	**result;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			counter++;
		i++;
	}
	result = malloc((counter + 1) * (sizeof(char *)));
	if (!result)
		return (0);
	result[counter] = 0;
	return (ft_fill_array(s, c, result));
}

/*
static char	**ft_fillsplit(char const *s, char c, char **arr)
{
	char	*start;
	char	*end;
	int		i;

	end = (char *)s;
	i = 0;
	while (1)
	{
		start = end;
		end = ft_strchr(end, c);
		if (!end || !*end)
			break ;
		if (end - start == 1)
			continue ;
		arr[i] = ft_substr(start, 0, end - start);
		end++;
		i++;
	}
	arr[i] = ft_substr(start, 0, end - start);
	arr[i + 1] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	*start;
	char	**result;

	if (!s)
		return (0);
	i = 1;
	start = (char *)s;
	while (1)
	{
		start = ft_strchr(start, c);
		if (!start || !*start)
			break ;
		if (start)
			start++;
		i++;
	}
	result = malloc((i + 2) * sizeof(char *));
	if (!result)
		return (0);
	return (ft_fillsplit(s, c, result));
}*/
