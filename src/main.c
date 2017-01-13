/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 08:46:09 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/13 10:21:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <unistd.h>

int		g_multifile;
t_len	g_size;

void	init_size(void)
{
	g_size.max_nblink = 0;
	g_size.max_user = 0;
	g_size.max_gr = 0;
	g_size.max_size = 0;
	g_size.max_major = 0;
	g_size.max_minor = 0;
}

int	main(int ac, const char *av[])
{
	char	*optstring;
	int		ret;

	init_size();
	optstring = ft_strdup("Ralrt");
	while ((ret = ft_getopt(ac, av, optstring)) != -1)
	{
		if (ret == '?')
		{
			write(2, "usage: ft_ls [Ralrt] [file ...]\n", 32);
			return (0);
		}
		opt_to_bits(ret);
	}
	free(optstring);
	if (!(av[g_optind]))
		ft_ls(".");
	else if (ac - g_optind > 1)
		sort_arg(ac, av);
	else
		ft_ls(av[g_optind]);
	return (0);
}
