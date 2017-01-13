/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:04:46 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/12 13:06:45 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	cmp(void *s1, void *s2, const char *path)
{
	int i;

	i = 0;
	(void)path;
	while (((char*)s1)[i] && ((char*)s2)[i])
	{
		if (((char*)s1)[i] != ((char*)s2)[i])
			break ;
		i++;
	}
	return (((char*)s1)[i] - ((char*)s2)[i]);
}

int	cmp_time(void *s1, void *s2, const char *path)
{
	char		*path1;
	char		*path2;
	struct stat	tmp1;
	struct stat	tmp2;

	path1 = ft_strjoin(path, "/");
	path2 = ft_strjoin(path, "/");
	path1 = ft_stradd(path1, (char*)s1);
	path2 = ft_stradd(path2, (char*)s2);
	lstat(path1, &tmp1);
	lstat(path2, &tmp2);
	return (tmp2.st_mtimespec.tv_sec - tmp1.st_mtimespec.tv_sec);
}

int	cmp_arg_time(void *s1, void *s2)
{
	struct stat	tmp1;
	struct stat	tmp2;

	lstat(s1, &tmp1);
	lstat(s2, &tmp2);
	return (tmp2.st_mtimespec.tv_sec - tmp1.st_mtimespec.tv_sec);
}

int	cmp_arg(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2));
}
