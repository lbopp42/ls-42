/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:06:43 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:43:51 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*create_lst(const char *content, t_list *next)
{
	t_list	*lst;

	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	lst->content = ft_strdup(content);
	lst->next = next;
	return (lst);
}

void	new_list(t_list **lst, const char *content,
		int (*f)(void *s1, void *s2))
{
	t_list	*tmp;

	if (*lst == NULL)
		*lst = create_lst(content, NULL);
	else if ((*f)((char*)content, (*lst)->content) > 0)
	{
		if (g_optls & LS_REV)
		{
			tmp = (*lst);
			(*lst) = create_lst(content, tmp);
		}
		else
			new_list(&((*lst)->next), content, f);
	}
	else if ((*f)((char*)content, (*lst)->content) <= 0)
	{
		if (g_optls & LS_REV)
			new_list(&((*lst)->next), content, f);
		else
		{
			tmp = (*lst);
			(*lst) = create_lst(content, tmp);
		}
	}
}

void	clean_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}
