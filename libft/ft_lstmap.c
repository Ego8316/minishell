/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:08:01 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:38:49 by ego              ###   ########.fr       */
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
t_list	*ft_lstmap_free(t_list *lst, void (*del)(void *))
{
	t_list	*node;

	while (lst)
	{
		node = lst->next;
		del(lst->content);
		free(lst);
		lst = node;
	}
	return (NULL);
}

/** 
 * @brief Applies a function to each node in a linked list
 * and returns a new list.
 * 
 * @param lst The linked list.
 * @param f The function to apply to each node.
 * @param del The function used to delete a node's content if needed.
 * 
 * @return The new linked list.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	if (!lst)
		return (NULL);
	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	node = head;
	while (lst)
	{
		node->content = f(lst->content);
		lst = lst->next;
		if (lst)
		{
			node->next = (t_list *)malloc(sizeof(t_list));
			if (!(node->next))
				return (ft_lstmap_free(head, del));
			node = node->next;
		}
	}
	node->next = NULL;
	return (head);
}
