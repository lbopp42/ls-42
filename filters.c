/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:25:49 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 16:31:46 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <sys/stat.h>

int	filter_name(t_node *tree, const void *content, size_t content_size)
{
	char	*basename;

	(void)content_size;
	basename = ft_strrchr((char *)tree->content, '/');
	if (basename != NULL)
		return (ft_strcmp(basename + 1, content));
	else
		return (ft_strcmp(tree->content, content));
}

int	filter_name_rev(t_node *tree, const void *content, size_t content_size)
{
	char	*basename;

	(void)content_size;
	basename = ft_strrchr((char *)tree->content, '/');
	if (basename != NULL)
		return (-ft_strcmp(basename + 1, content));
	else
		return (-ft_strcmp(tree->content, content));
}

int	filter_time(t_node *tree, const void *content, size_t content_size)
{
	struct stat	st_buf;
	struct stat	st_buf_tree;

	(void)content_size;
	stat((char *)content, &st_buf);
	stat((char *)tree->content, &st_buf_tree);
	if (st_buf_tree.st_mtimespec.tv_nsec >= st_buf.st_mtimespec.tv_nsec)
		return (1);
	return (0);
}

int	filter_time_rev(t_node *tree, const void *content, size_t content_size)
{
	struct stat	st_buf;
	struct stat	st_buf_tree;

	(void)content_size;
	stat((char *)content, &st_buf);
	stat((char *)tree->content, &st_buf_tree);
	if (st_buf_tree.st_mtimespec.tv_nsec < st_buf.st_mtimespec.tv_nsec)
		return (1);
	return (0);
}
