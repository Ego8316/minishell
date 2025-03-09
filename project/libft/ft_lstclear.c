/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:55:03 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:38:21 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes the content of each node and frees them afterwards.
 * 
 * @param lst The linked list to be freed.
 * @param del The function used to delete a node's content.
 * 
 * @return NULL.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;
	t_list	*temp;

	l = *lst;
	while (l)
	{
		temp = l->next;
		ft_lstdelone(l, del);
		l = temp;
	}
	*lst = NULL;
}
