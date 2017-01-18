/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 10:39:13 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:45:30 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*before_read(t_node *tree, const char *dir_path)
{
	DIR				*dir;
	static int		i = 0;
	static int		nb_file = 0;
	int				j;
	struct dirent	*lecture;

	j = 0;
	dir = 0;
	if ((g_multifile == 1 && i != 0) || (g_optls & LS_RECUR && i != 0))
		write(1, "\n", 1);
	if (i != 0 || g_multifile == 1)
		ft_putendstr(dir_path, ":\n");
	i++;
	if (!(dir = opendir(dir_path)))
		error_open(dir_path);
	else
	{
		while ((lecture = readdir(dir)))
			readding_dir(&tree, lecture, dir_path);
		closedir(dir);
		print_tree(tree, dir_path, &j, &nb_file);
		to_recur(tree, dir_path);
		clean_tree(tree);
	}
	return (tree);
}

void	to_recur(t_node *tree, const char *dir_path)
{
	if (g_optls & LS_RECUR)
		create_recur_tree(tree, dir_path);
}

void	readding_dir(t_node **tree, struct dirent *lecture, const char *path)
{
	if (ft_strcmp(lecture->d_name, ".") && ft_strcmp(lecture->d_name, "..")
			&& g_optls & LS_NOPOINT)
	{
		if (g_optls & LS_SIZE)
			add_node(tree, lecture, cmp_size, path);
		else if (g_optls & LS_TIME)
			add_node(tree, lecture, cmp_time, path);
		else
			add_node(tree, lecture, cmp, path);
	}
	else if (lecture->d_name[0] == '.' && g_optls & LS_ALL)
	{
		if (g_optls & LS_SIZE)
			add_node(tree, lecture, cmp_size, path);
		else if (g_optls & LS_TIME)
			add_node(tree, lecture, cmp_time, path);
		else
			add_node(tree, lecture, cmp, path);
	}
	else if (lecture->d_name[0] != '.')
		normal_treat(tree, lecture, path);
}

void	normal_treat(t_node **tree, struct dirent *lecture, const char *path)
{
	if (g_optls & LS_SIZE)
		add_node(tree, lecture, cmp_size, path);
	else if (g_optls & LS_TIME)
		add_node(tree, lecture, cmp_time, path);
	else
		add_node(tree, lecture, cmp, path);
}
