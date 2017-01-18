/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 13:21:23 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:43:17 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*create_btree(struct dirent *content, t_node *next_dir, t_node *in_dir,
		const char *path)
{
	t_node	*tree;
	char	*newpath;

	if (!(tree = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	if (!(tree->content = (struct dirent*)malloc(sizeof(struct dirent))))
		return (NULL);
	newpath = ft_strjoin(path, "/");
	newpath = ft_stradd(newpath, content->d_name);
	if (lstat(newpath, &tree->st) == -1)
	{
		tree->bug = 1;
		error_lstat(content->d_name);
	}
	if (ft_strlen(content->d_name) > g_size.max_name)
		g_size.max_name = ft_strlen(content->d_name);
	free(newpath);
	if ((g_optls & LS_LONG || g_optls & LS_NOGRID) && tree->bug == 0)
		btree_long(&tree);
	ft_memcpy(tree->content, content, sizeof(*content));
	tree->next_dir = next_dir;
	tree->in_dir = in_dir;
	return (tree);
}

void	add_node(t_node **tree, struct dirent *content,
		int (*f)(struct dirent *content, struct dirent *tcontent
			, const char *path), const char *path)
{
	t_node *tmp;

	tmp = NULL;
	if (*tree == NULL)
		*tree = create_btree(content, NULL, NULL, path);
	else if ((*f)(content, (*tree)->content, path) > 0)
	{
		if (g_optls & LS_REV)
		{
			tmp = *tree;
			*tree = create_btree(content, tmp, NULL, path);
		}
		else
			add_node(&(*tree)->next_dir, content, f, path);
	}
	else if ((*f)(content, (*tree)->content, path) <= 0)
	{
		if (g_optls & LS_REV)
			add_node(&(*tree)->next_dir, content, f, path);
		else
		{
			tmp = *tree;
			*tree = create_btree(content, tmp, NULL, path);
		}
	}
}

void	create_recur_tree(t_node *tree, const char *dir_path)
{
	char	*newpath;

	while (tree != NULL)
	{
		if (S_ISDIR(tree->st.st_mode) && ft_strcmp(tree->content->d_name,
					".") && ft_strcmp(tree->content->d_name, ".."))
		{
			if (ft_strcmp(dir_path, "/"))
				newpath = ft_strjoin(dir_path, "/");
			else
				newpath = ft_strdup(dir_path);
			newpath = ft_stradd(newpath, tree->content->d_name);
			tree->in_dir = before_read(tree->in_dir, newpath);
			free(newpath);
		}
		tree = tree->next_dir;
	}
}

void	clean_tree(t_node *tree)
{
	if (tree == NULL)
		return ;
	clean_tree(tree->next_dir);
	free(tree->content);
	free(tree);
}
