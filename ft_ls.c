/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:19:51 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 13:43:34 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

void			ft_ls(char *path, int options)
{
	int			active_opts;
	int			(*filter_func[])(t_node *, const void *, size_t) = {
		&filter_name_rev,
		&filter_time,
		&filter_time_rev,
		&filter_name,
	};
	const int	filters[] = { FT_REVERSE, FT_TIME, FT_TIME_REV, FT_NAME };
	int			i;

	i = 0;
	while (i < NB_FILTERS)
	{
		if (options & filters[i])
			ft_ls_start(path, filter_func[i], options);
		i++;
	}
}

t_node	*ft_node_new(void *content, size_t content_size)
{
	t_node	*tree;

	tree = (t_node *)malloc(sizeof(t_node));
	if (content && content_size > 0)
	{
		tree->content = (void *)malloc(content_size);
		ft_memcpy(tree->content, content, content_size);
		tree->content_size = content_size;
	}
	else
	{
		tree->content = NULL;
		tree->content_size = 0;
	}
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

int			ft_node_add(t_node *tree, void *content, size_t content_size,
		int (*f)(t_node *, const void *, size_t))
{
	if (f(tree, content, content_size) < 0)
	{
		if (tree->left)
			ft_node_add(tree->left, content, content_size, f);
		else
			tree->left = ft_node_new(content, content_size);
	}
	else
	{
		if (tree->right)
			ft_node_add(tree->right, content, content_size, f);
		else
			tree->right = ft_node_new(content, content_size);
	}
	return (1);
}

void		ft_treeprint(t_node *tree)
{
	if (tree->left)
		ft_treeprint(tree->left);
	ft_putendl(tree->content);
	if (tree->right)
		ft_treeprint(tree->right);
}

void		ft_ls_start(char *path,
		int (*f)(t_node *, const void *, size_t), int options)
{
	DIR				*dir_p;
	struct dirent	*buf;
	t_node			*tree;

	dir_p = opendir(path);
	tree = NULL;
	while ((buf = readdir(dir_p)) != NULL)
	{
		if (tree == NULL)
			tree = ft_node_new(path, ft_strlen(path) + 1);
		else
			ft_node_add(tree, path, ft_strlen(path) + 1, f);
	}
	ft_treeprint(tree);
}
