/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 10:39:13 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/12 14:12:16 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

t_node	*before_read(t_node *tree, const char *dir_path)
{
	DIR				*dir;
	struct dirent	*lecture;
	char			*path;
	static int		i = 0;
	char			*name;
	int		j;

	j = 0;
	dir = 0;
	if ((g_multifile == 1 && i != 0) || (g_optls & LS_RECUR && i != 0))
		write(1, "\n", 1);
	if (i != 0 || g_multifile == 1)
	{
		path = ft_strdup(dir_path);
		path = ft_stradd(path, ":");
		ft_putendl(path);
		free(path);
	}
	i++;
	if (!(dir = opendir(dir_path)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		name = ft_strrchr(dir_path, '/') + 1;
		name = ft_strjoin(name, ":");
		ft_putendch_fd(name, ' ', 2);
		free(name);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
	{
		while ((lecture = readdir(dir)))
			readding_dir(&tree, lecture, dir_path);
		closedir(dir);
		print_tree(tree, dir_path, &j);
		if (g_optls & LS_RECUR)
			create_recur_tree(tree, dir_path);
	}
	return (tree);
}

void	readding_dir(t_node **tree, struct dirent *lecture, const char *path)
{
	if (g_optls & LS_ALL)
	{
		if (g_optls & LS_TIME)
			add_node(tree, lecture, cmp_time, path);
		else
			add_node(tree, lecture, cmp, path);
	}
	else if (lecture->d_name[0] != '.')
	{
		if (g_optls & LS_TIME)
			add_node(tree, lecture, cmp_time, path);
		else
			add_node(tree, lecture, cmp, path);
	}
}

void	print_multi(t_list *lst_arg)
{
	while (lst_arg != NULL)
	{
		ft_ls(lst_arg->content);
		lst_arg = lst_arg->next;
	}
}

void	sort_arg(int ac, const char *av[])
{
	t_list *lst_arg;

	lst_arg = NULL;
	while (g_optind < ac)
	{
		g_multifile = 1;
		if (g_optls & LS_TIME)
			new_list(&lst_arg, av[g_optind], &cmp_arg_time);
		else
			new_list(&lst_arg, av[g_optind], &cmp_arg);
		g_optind++;
	}
	print_multi(lst_arg);
	clean_lst(lst_arg);
}

t_node	*ft_ls(const char *dir_path)
{
	t_node			*tree;

	tree = NULL;
	tree = before_read(tree, dir_path);
	clean_tree(tree);
	return (tree);
}
