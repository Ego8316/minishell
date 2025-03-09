/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:16:36 by pkurt             #+#    #+#             */
/*   Updated: 2024/10/06 12:16:54 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	if ((*lst)->next)
	{
		next = (*lst)->next;
		ft_lstclear(&next, del);
	}
	del((*lst)->content);
	free(*lst);
	*lst = 0;
}
