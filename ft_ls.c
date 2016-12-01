/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:19:51 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 11:41:18 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include "libft.h"

void			ft_ls(char *path, int options)
{
	int			active_opts;
	const int	(*filter_func[])(t_node *, const void *, const void *) = {
		&filter_name_rev,
		&filter_time,
		&filter_time_rev,
		&filter_name,
	};
	const int	filters[] = { FT_REVERSE, FT_TIME, FT_TIME_REV, FT_NAME };
	int			i;

	i = 0;
	while (i < NB_FILTERS)
	{
		if (options & filters[i])
			ft_ls_start(path, filter[i], options);
		i++;
	}
}

t_node	*ft_node_new(void *content, size_t content_size)
{
	t_node	*tree;

	tree = (t_node *)malloc(sizeof(t_node));
	if (content && content_size > 0)
	{
		tree->content = (void *)malloc(content_size);
		ft_memcpy(tree->content, content, content_size);
		tree->content_size = content_size;
	}
	else
	{
		tree->content = NULL;
		tree->content_size = 0;
	}
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_file	*ft_file_new(char *name)
{
	t_file	*file;
	
	file = (t_file *)malloc(sizeof(t_file));
	t_file->name = ft_strdup(name);
	return (file);
}

struct stat		*get_stat(char *path)
{
	struct stat	st_buf;
	struct stat	*st;

	lstat(path, &st_buf);
	st = (struct stat *)malloc(sizeof(struct stat));
	st->st_uid = st_buf.st_uid;
	st->st_gid = st_buf.st_gid;
	st->st_mtimespec = st_buf.st_mtimespec;
	return (st);
}

struct passwd	*get_passwd(uid_t uid)
{
	struct passwd	*buf_pwd;
	struct passwd	*pwd;

	buf_pwd = getpwuid(uid);
	pwd = (struct passwd *)malloc(sizeof(struct passwd));
	pwd->pw_name = ft_strdup(buf_pwd.pw_name);
	return (pwd);
}

t_file			get_file(char *path)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));

}

void		ft_ls_start(char *path,
		int (*f)(t_node *, const void *, const void *), int options)
{
	DIR				*dir_p;
	struct dirent	*buf;
	t_node			*tree;
	t_file			*file;

	struct passwd	*buf_pwd;
	struct group	*buf_grp;

	dir_p = opendir(path);
	tree = NULL;
	while (buf = readdir(dir_p) != NULL)
	{
		file = ft_file_new(buf->d_name);
		file->st = get_stat(path);
		file->st = get_passwd(file->st.st_uid);
		if (!(tree = ft_node_new()))
	}
}
