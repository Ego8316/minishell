/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:16:47 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/06 12:16:54 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;
	void	*content;

	first = 0;
	while (lst && f && del)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (!new)
		{
			free(content);
			ft_lstclear(&first, del);
			return (0);
		}
		if (!first)
			first = new;
		else
			ft_lstlast(first)->next = new;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (first);
}
