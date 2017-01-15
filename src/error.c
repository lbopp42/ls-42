/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 09:12:32 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/15 14:07:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_lstat(char *name)
{
	ft_putendch_fd("ft_ls:", ' ', 2);
	name = ft_strjoin(name, ":");
	ft_putendch_fd(name, ' ', 2);
	free(name);
	ft_putendl_fd(strerror(errno), 2);
}
