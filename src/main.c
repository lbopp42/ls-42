/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:06:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/05 16:11:15 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, const char *av[])
{
	int		ret;
	char	*optstring;

	optstring = "Rarlt";
	g_option = 0;
	g_multi = 0;
	while ((ret = ft_getopt(ac, av, optstring)) != -1)
		put_opt_binary(ret);
	if (ac - g_optind > 1)
		sort_arg(ac, av);
	else
		ft_ls(av[g_optind]);
	return (0);
}
