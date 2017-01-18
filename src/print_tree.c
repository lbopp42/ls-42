/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:08:22 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:45:18 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_color(t_node *tree)
{
	char	*color;

	ft_putstr("\033[1m");
	if (S_ISBLK(tree->st.st_mode))
		color = ft_strdup("\033[31m");
	else if (S_ISCHR(tree->st.st_mode))
		color = ft_strdup("\033[34m");
	else if (S_ISDIR(tree->st.st_mode))
		color = ft_strdup("\033[36m");
	else if (S_ISLNK(tree->st.st_mode))
		color = ft_strdup("\033[35m");
	else if (S_ISSOCK(tree->st.st_mode))
		color = ft_strdup("\033[33m");
	else if (S_ISFIFO(tree->st.st_mode))
		color = ft_strdup("\033[37m");
	else
		color = ft_strdup("\033[32m");
	ft_putstr(color);
	free(color);
}

void	print_long(int *i, t_node *tree, const char *dir_path)
{
	char	*file_path;
	char	str[255];

	file_path = ft_strdup(dir_path);
	file_path = ft_stradd(file_path, "/");
	file_path = ft_stradd(file_path, tree->content->d_name);
	if (*i == 1)
		print_total();
	print_color(tree);
	long_format(tree, dir_path);
	bzero(str, 255);
	readlink(file_path, str, 255);
	free(file_path);
	if (str[0])
	{
		ft_putendstr(tree->content->d_name, " -> ");
		ft_putendl(str);
	}
	else
		ft_putendl(tree->content->d_name);
}

void	print_in_col(t_node *tree, int *nb_file)
{
	ft_putstr(tree->content->d_name);
	print_space(g_size.max_name + 1
			, ft_strlen(tree->content->d_name));
	*nb_file += 1;
	if ((unsigned long)*nb_file + 1 > nb_col() / (g_size.max_name + 1))
	{
		*nb_file = 0;
		write(1, "\n", 1);
	}
	if (tree->next_dir == NULL)
		write(1, "\n", 1);
}

void	print_tree(t_node *tree, const char *dir_path, int *i, int *nb_file)
{
	*nb_file = 0;
	while (tree != NULL)
	{
		if (tree->bug == 1)
			return ;
		*i += 1;
		print_color(tree);
		if (g_optls & LS_LONG || g_optls & LS_NOGRID)
			print_long(i, tree, dir_path);
		else if (g_optls & LS_COL)
			ft_putendl(tree->content->d_name);
		else
			print_in_col(tree, nb_file);
		ft_putstr("\033[0m");
		tree = tree->next_dir;
	}
	init_size();
}
