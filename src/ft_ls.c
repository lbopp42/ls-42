/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:01:02 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/06 09:45:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

void	sort_arg(int ac, const char *av[])
{
	t_list	*lst_arg;

	lst_arg = NULL;
	while (g_optind < ac)
	{
		g_multi = 1;
		if (g_option & LS_TIME)
			new_list(&lst_arg, av[g_optind], ft_strlen(av[g_optind]), &cmp_arg_time);
		else
			new_list(&lst_arg, av[g_optind], ft_strlen(av[g_optind]), &cmp_arg);
		g_optind++;
	}
	while (lst_arg != NULL)
	{
		ft_ls(lst_arg->content);
		lst_arg = lst_arg->next;
	}
}

int		ft_ls(const char *path)
{
	t_node	*tree;

	tree = NULL;
	if (path == NULL)
		path = ".";
	g_path = path;
	tree = put_in_tree(tree, path);
	clean_tree(tree);
	return (1);
}
