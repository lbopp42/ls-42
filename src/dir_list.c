/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:19:11 by lbopp             #+#    #+#             */
/*   Updated: 2016/12/17 13:05:24 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_lstaddend(t_list *lst, char	*content, int content_size)
{
	t_list	*new;
	t_list *temp;

	new = (t_list*)malloc(sizeof(t_list));
	new->content = (char*)malloc(sizeof(char) * content_size);
	new->content = content;
	new->next = NULL;
	if (lst == NULL)
		return (new);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (lst);
}
