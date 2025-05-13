/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:31:47 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 14:02:48 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	strb_join(char **str, char *end)
{
	char	*new;
	int		strl;
	int		endl;

	strl = ft_strlen_null(*str);
	endl = ft_strlen_null(end);
	new = malloc(sizeof(char) * (strl + endl + 1));
	if (new)
	{
		new[strl + endl] = 0;
		if (*str)
			ft_memcpy(new, *str, sizeof(char) * strl);
		if (end)
			ft_memcpy(new + strl, end, sizeof(char) * endl);
	}
	if (*str)
		free(*str);
	if (end)
		free(end);
	if (new)
		*str = new;
	else
		*str = 0;
	return (new != 0);
}

t_bool	strb_append(char **str, char end)
{
	char	*new;
	int		strl;

	strl = ft_strlen_null(*str);
	new = malloc(sizeof(char) * (strl + 2));
	if (new)
	{
		new[strl + 1] = 0;
		new[strl] = end;
		if (*str)
			ft_memcpy(new, *str, sizeof(char) * strl);
	}
	if (*str)
		free(*str);
	if (new)
		*str = new;
	else
		*str = 0;
	return (new != 0);
}

char	*strb_new(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (str)
		str[0] = 0;
	return (str);
}

t_bool	strb_sub(char *str, int start, int count, char **ret)
{
	*ret = 0;
	*ret = ft_substr(str, start, count);
	return (*ret != 0);
}
