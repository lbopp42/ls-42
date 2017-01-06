/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:06:43 by lbopp             #+#    #+#             */
/*   Updated: 2016/12/17 13:07:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*create_lst(const char *content, size_t content_size, t_list *next)
{
	t_list	*lst;

	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(lst->content = (char*)malloc(sizeof(char) * content_size)))
		return (NULL);
	lst->content = (char*)content;
	lst->next = next;
	return (lst);
}

void	new_list(t_list **lst, const char *content, size_t content_size, int (*f)(void *s1, void *s2))
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = create_lst(content, ft_strlen(content), NULL);
	}
	else if ((*f)((char*)content, (*lst)->content) > 0)
	{
		if (g_option & LS_REV)
		{
			tmp = (*lst);
			(*lst) = create_lst(content, ft_strlen(content), tmp);
		}
		else
			new_list(&((*lst)->next), content, content_size, f);
	}
	else if ((*f)((char*)content, (*lst)->content) <= 0)
	{
		if (g_option & LS_REV)
			new_list(&((*lst)->next), content, content_size, f);
		else
		{
			tmp = (*lst);
			(*lst) = create_lst(content, ft_strlen(content), tmp);
		}
	}
}
