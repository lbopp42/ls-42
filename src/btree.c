/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 08:55:16 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/06 10:01:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		tree_is_empty(t_node *tree)
{
	if (tree == NULL)
		return (1);
	else
		return (0);
}

void	clean_tree(t_node *tree)
{
	if (tree == NULL)
		return ;
	clean_tree(tree->child);
	clean_tree(tree->brother);
	free(tree);
}

t_node	*create_btree(struct dirent *info, t_node *brother, t_node *child, const char *path)
{
	t_node	*tree;
	char	*newpath;

	if (!(tree = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	if (!(tree->content = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	if (!(tree->content->info = (struct dirent*)malloc(sizeof(struct dirent))))
		return (NULL);
	ft_memcpy(tree->content->info, info, sizeof(*info));
	if (ft_strcmp(path, "/") == 0)
		path = "";
	if (g_option & LS_LONG)
	{
		newpath = ft_strjoin(path, "/");
		newpath = ft_stradd(newpath, info->d_name);
		lstat(newpath, &tree->content->st);
		if (!(tree->content->pass = (struct passwd*)malloc(sizeof(struct passwd))))
			return (NULL);
		tree->content->pass = getpwuid(tree->content->st.st_uid);
		if (!(tree->content->gr = (struct group*)malloc(sizeof(struct group))))
			return (NULL);
		tree->content->gr = getgrgid(tree->content->pass->pw_gid);
	}
	tree->brother = brother;
	tree->child = child;
	return (tree);
}

void	new_node(t_node **tree, struct dirent *content, int (*f)(void *s1, void *s2, const char *path), const char *path)
{
	t_node	*tmp;

	if (*tree == NULL)
		*tree = create_btree(content, NULL, NULL, path);
	else if ((*f)(content->d_name, (*tree)->content->info->d_name, path) > 0)
		if (g_option & LS_REV)
		{
			tmp = (*tree);
			(*tree) = create_btree(content, tmp, NULL, path);
		}
		else
			new_node(&((*tree)->brother), content, f, path);
	else if ((*f)(content->d_name, (*tree)->content->info->d_name, path) <= 0)
	{
		if (g_option & LS_REV)
			new_node(&((*tree)->brother), content, f, path);
		else
		{
			tmp = (*tree);
			(*tree) = create_btree(content, tmp, NULL, path);
		}
	}
}
