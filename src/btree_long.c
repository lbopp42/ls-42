/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:01:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/13 11:18:52 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

void	btree_long(struct dirent *content, const char *path, t_node **tree)
{
	char	*newpath;
	char	*name;

	newpath = ft_strjoin(path, "/");
	newpath = ft_stradd(newpath, content->d_name);
	if (lstat(newpath, &(*tree)->st) == -1)
	{
		free(newpath);
		ft_putendsp("ft_ls:");
		name = ft_strjoin(content->d_name, ":");
		ft_putendsp(name);
		free(name);
		ft_putendl(strerror(errno));
		return;
	}
	free(newpath);
	if (ft_nbrlen((*tree)->st.st_nlink) > g_size.max_nblink)
		g_size.max_nblink = ft_nbrlen((*tree)->st.st_nlink);
	if (ft_strlen(getpwuid((*tree)->st.st_uid)->pw_name) > g_size.max_user)
		g_size.max_user = ft_strlen(getpwuid((*tree)->st.st_uid)->pw_name);
	if (ft_strlen(getgrgid((*tree)->st.st_gid)->gr_name) > g_size.max_gr)
		g_size.max_gr = ft_strlen(getgrgid((*tree)->st.st_gid)->gr_name);
	if (ft_nbrlen((*tree)->st.st_size) > g_size.max_size)
		g_size.max_size = ft_nbrlen((*tree)->st.st_size);
	if (ft_nbrlen(major((*tree)->st.st_rdev)) > g_size.max_major)
		g_size.max_major = ft_nbrlen(major((*tree)->st.st_rdev));
	if (ft_nbrlen(minor((*tree)->st.st_rdev)) > g_size.max_minor)
		g_size.max_minor = ft_nbrlen(minor((*tree)->st.st_rdev));
}
