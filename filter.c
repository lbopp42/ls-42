/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:25:49 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 10:00:23 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>

int	filter_name(t_node *tree, const void *content, size_t content_size)
{
	(void)content_size;
	return (ft_strcmp(tree->content->name, content->name))
}

int	filter_name_rev(t_node *tree, const void *content, size_t content_size)
{
	(void)content_size;
	return (-ft_strcmp(tree->content->name, conten->name));
}

int	filter_time(t_node *tree, const void *content, size_t content_size)
{
	if (tree->file->st.st_mtimespec.tv_nsec >= content->st.st_mtimespec.tv_nsec)
		return (1);
	return (0);
}

int	filter_time_rev(t_node *tree, const void *content, size_t content_size)
{
	if (tree->file->st.st_mtimespec.tv_nsec < content->st.st_mtimespec.tv_nsec)
		return (1);
	return (0);
}
