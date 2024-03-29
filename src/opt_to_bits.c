/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_to_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 09:10:04 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:45:04 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	g_optls = 0;

void	opt_to_bits(int opt)
{
	if (opt == 'R')
		g_optls = LS_RECUR | g_optls;
	if (opt == 'a')
		g_optls = g_optls | LS_ALL;
	if (opt == 'l')
		g_optls = LS_LONG | g_optls;
	if (opt == 'r')
		g_optls = g_optls | LS_REV;
	if (opt == 't')
		g_optls = LS_TIME | g_optls;
	if (opt == 'A')
		g_optls = LS_NOPOINT | g_optls;
	if (opt == '1')
		g_optls = LS_COL | g_optls;
	if (opt == 'o')
		g_optls = LS_NOGRID | g_optls;
	if (opt == 'S')
		g_optls = LS_SIZE | g_optls;
}
