/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:59:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/05 15:44:29 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*g_optarg = 0;
int		g_optind = 1;
int		g_optopt = 0;
int		g_opterr = 1;
int		g_optreset = 0;

int	treatment_opt(const char *av[], int *i, const char *optstring)
{
	if (ft_strchr(optstring, av[g_optind][*i]))
	{
		*i += 1;
		g_optopt = av[g_optind][*i - 1];
		return (av[g_optind][*i - 1]);
	}
	else
	{
		if (g_opterr)
		{
			write(1, av[0], ft_strlen(av[0]));
			write(1, ": illegal option -- ", 20);
			write(1, &(av[g_optind][*i]), 1);
			write(1, "\n", 1);
		}
		*i += 1;
		g_optopt = av[g_optind][*i - 1];
		return ('?');
	}
}

int	ft_getopt(int ac, const char *av[], const char *optstring)
{
	static int	i = 1;
	int			ret;

	if (ac >= 2)
	{
		if (av[g_optind][0] == '-' && av[g_optind][1] == '-')
			return (-1);
		if (av[g_optind][i] != '\0' && av[g_optind][0] == '-')
		{
			if ((ret = treatment_opt(av, &i, optstring)))
			{
				optind++;
				return (ret);
			}
		}
		if (av[g_optind][i] == '\0' && av[g_optind][0] == '-')
			g_optind++;
	}
	return (-1);
}
