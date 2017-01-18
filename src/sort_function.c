/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:04:46 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:45:44 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	cmp(struct dirent *content, struct dirent *tcontent, const char *path)
{
	(void)path;
	return (ft_strcmp(content->d_name, tcontent->d_name));
}

int	cmp_size(struct dirent *content, struct dirent *tcontent, const char *path)
{
	char		*path1;
	char		*path2;
	struct stat	tmp1;
	struct stat	tmp2;

	path1 = ft_strdup(path);
	path1 = ft_stradd(path1, "/");
	path2 = ft_strdup(path);
	path2 = ft_stradd(path2, "/");
	path1 = ft_stradd(path1, content->d_name);
	path2 = ft_stradd(path2, tcontent->d_name);
	lstat(path1, &tmp1);
	lstat(path2, &tmp2);
	free(path1);
	free(path2);
	if (tmp2.st_size != tmp1.st_size)
		return (tmp2.st_size - tmp1.st_size);
	else
		return (cmp(content, tcontent, path));
}

int	cmp_time(struct dirent *content, struct dirent *tcontent, const char *path)
{
	char		*path1;
	char		*path2;
	struct stat	tmp1;
	struct stat	tmp2;

	path1 = ft_strdup(path);
	path1 = ft_stradd(path1, "/");
	path2 = ft_strdup(path);
	path2 = ft_stradd(path2, "/");
	path1 = ft_stradd(path1, content->d_name);
	path2 = ft_stradd(path2, tcontent->d_name);
	lstat(path1, &tmp1);
	lstat(path2, &tmp2);
	free(path1);
	free(path2);
	if (tmp2.st_mtimespec.tv_sec - tmp1.st_mtimespec.tv_sec)
		return (tmp2.st_mtimespec.tv_sec - tmp1.st_mtimespec.tv_sec);
	else
		return (tmp2.st_mtimespec.tv_nsec - tmp1.st_mtimespec.tv_nsec ?
				tmp2.st_mtimespec.tv_nsec - tmp1.st_mtimespec.tv_nsec :
				cmp(content, tcontent, path));
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
