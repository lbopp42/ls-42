/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 11:18:19 by lbopp             #+#    #+#             */
/*   Updated: 2016/12/14 11:03:47 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	put_opt_binary(int ret)
{
	if (ret == 'R')
		g_option = g_option | LS_RECUR;
	if (ret == 'a')
		g_option = g_option | LS_ALL;
	if (ret == 'l')
		g_option = g_option | LS_LONG;
	if (ret == 'r')
		g_option = g_option | LS_REV;
	if (ret == 't')
		g_option = g_option | LS_TIME;
}
