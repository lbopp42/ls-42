/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 13:49:12 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:43:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	return (tree);
}
