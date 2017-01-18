/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 09:12:32 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:43:36 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_lstat(const char *name)
{
	char	*newname;

	newname = ft_strdup(name);
	ft_putendch_fd("ft_ls:", ' ', 2);
	ft_putendstr_fd(newname, ": ", 2);
	free(newname);
	ft_putendl_fd(strerror(errno), 2);
}

void	error_open(const char *dir_path)
{
	if (ft_strrchr(dir_path, '/') != NULL && errno != ENOENT)
		error_lstat(ft_strrchr(dir_path, '/') + 1);
	else
		error_lstat(dir_path);
}
