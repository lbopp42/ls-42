/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:08:22 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/15 14:07:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

void	print_tree(t_node *tree, const char *dir_path, int *i)
{
	char	str[255];
	char	*file_path;

	while (tree != NULL)
	{
		file_path = ft_strdup(dir_path);
		file_path = ft_stradd(file_path, "/");
		file_path = ft_stradd(file_path, tree->content->d_name);
		if ((g_optls & LS_RECUR || g_optls & LS_LONG) &&
			lstat(file_path, &tree->st) == -1)
			return ;
		if (g_optls & LS_LONG)
		{
			if (*i == 0)
				print_total(tree);
			*i += 1;
			long_format(tree, dir_path);
			bzero(str, 255);
			readlink(file_path, str, 255);
			free(file_path);
			if (str[0])
			{
				ft_putendsp(tree->content->d_name);
				ft_putendsp("->");
				ft_putendl(str);
			}
			else
				ft_putendl(tree->content->d_name);
		}
		else
			ft_putendl(tree->content->d_name);
		tree = tree->next_dir;
	}
}
