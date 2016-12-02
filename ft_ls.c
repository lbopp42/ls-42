/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:19:51 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/02 14:43:45 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"
#include <time.h>
#include <sys/types.h>

void		ft_ls(char *path, int options)
{
	static int	(*filter_func[5])(t_node *, const void *, size_t) = {
		&filter_name_rev,
		&filter_time,
		&filter_time_rev,
		&filter_name,
		&filter_name,
	};
	const int	filters[] = { FT_REVERSE, FT_TIME, FT_TIME_REV, FT_NAME,
		FT_NOOPT };
	int			i;

	i = 0;
	while (filters[i] != FT_NOOPT)
	{
		if (options & filters[i])
			ft_ls_start(path, filter_func[i], options);
		i++;
	}
	ft_ls_start(path, filter_func[i], options);
}

t_node		*ft_node_new(void *content, size_t content_size)
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

int			ft_node_add(t_node *tree, void *content, size_t content_size,
		int (*f)(t_node *, const void *, size_t))
{
	if (f(tree, content, content_size) < 0)
	{
		if (tree->left)
			ft_node_add(tree->left, content, content_size, f);
		else
			tree->left = ft_node_new(content, content_size);
	}
	else
	{
		if (tree->right)
			ft_node_add(tree->right, content, content_size, f);
		else
			tree->right = ft_node_new(content, content_size);
	}
	return (1);
}

char		*basename(char *s)
{
	char *basename;

	basename = ft_strrchr(s, '/');
	if (basename != NULL)
		return (basename + 1);
	else
		return (s);
}

char	get_file_type(mode_t st_mode){
	if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	return ('-');
}

char	*acl(mode_t st_mode)
{
	char	*s;

	s = ft_strnew(11);
	s[0] = get_file_type(st_mode);
	st_mode & S_IRUSR ? (s[1] = 'r') : (s[1] = '-');
	st_mode & S_IWUSR ? (s[2] = 'w') : (s[2] = '-');
	st_mode & S_IXUSR ? (s[3] = 'x') : (s[3] = '-');
	st_mode & S_IRGRP ? (s[4] = 'r') : (s[4] = '-');
	st_mode & S_IWGRP ? (s[5] = 'w') : (s[5] = '-');
	st_mode & S_IXGRP ? (s[6] = 'x') : (s[6] = '-');
	st_mode & S_IROTH ? (s[7] = 'r') : (s[7] = '-');
	st_mode & S_IWOTH ? (s[8] = 'w') : (s[8] = '-');
	st_mode & S_IXOTH ? (s[9] = 'x') : (s[9] = '-');
	s[10] = ' ';
	return (s);
}

char	*nb_link(nlink_t st_nlink)
{
	return (ft_itoa(st_nlink));
}

char		*get_owner(uid_t st_uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(st_uid);
	return (ft_strdup(pwd->pw_name));
}

char		*get_group(gid_t st_gid)
{
	struct group	*grp;

	grp = getgrgid(st_gid);
	return (ft_strdup(grp->gr_name));
}

char		*get_time(time_t time)
{
	char	*date;

	date = ctime(&time);
	ft_memmove(date, date + 4, ft_strlen(date + 4));
	*ft_strrchr(date, ':') = 0;
	return (date);
}

char		*get_file_size(off_t size)
{
	return (ft_itoa(size));
}

#include <stdio.h>

char		*get_maj(dev_t dev)
{
	return (ft_itoa(major(dev)));
}

char		*get_min(dev_t dev)
{
	return (ft_itoa(minor(dev)));
}

char		*long_ls(t_node *tree)
{
	char	*long_format;
	t_file	file;

	file.name = ft_strdup(tree->content);
	lstat(tree->content, &file.st);
	long_format = acl(file.st.st_mode);
	long_format = ft_stradd(long_format, nb_link(file.st.st_nlink));
	long_format = ft_stradd(long_format, " ");
	long_format = ft_stradd(long_format, get_owner(file.st.st_uid));
	long_format = ft_stradd(long_format, " ");
	long_format = ft_stradd(long_format, get_group(file.st.st_gid));
	long_format = ft_stradd(long_format, " ");
	if (S_ISCHR(file.st.st_mode) || S_ISBLK(file.st.st_mode))
	{
		long_format = ft_stradd(long_format, get_maj(file.st.st_rdev));
		long_format = ft_stradd(long_format, ", ");
		long_format = ft_stradd(long_format, get_min(file.st.st_rdev));
		long_format = ft_stradd(long_format, " ");
	}
	else
	{
		long_format = ft_stradd(long_format, get_file_size(file.st.st_size));
		long_format = ft_stradd(long_format, " ");
	}
	long_format = ft_stradd(long_format, get_time(file.st.st_mtimespec.tv_sec));
	long_format = ft_stradd(long_format, " ");
	return (long_format);
}

void		ft_treeprint(t_node *tree, int options)
{
	if (tree->left)
		ft_treeprint(tree->left, options);
	if (*basename(tree->content) == '.')
	{
		if (options & FT_ALL)
		{
			ft_putstr(long_ls(tree));
			ft_putendl(basename(tree->content));
		}
	}
	else
	{
		ft_putstr(long_ls(tree));
		ft_putendl(basename(tree->content));
	}
	if (tree->right)
		ft_treeprint(tree->right, options);
}

void		ft_ls_start(char *path,
		int (*f)(t_node *, const void *, size_t), int options)
{
	DIR				*dir_p;
	struct dirent	*buf;
	t_node			*tree;
	t_file			curr_f;

	dir_p = opendir(path);
	tree = NULL;
	while ((buf = readdir(dir_p)) != NULL)
	{
		curr_f.name = ft_strjoin(path, "/");
		curr_f.name = ft_stradd(curr_f.name, buf->d_name);
		if (tree == NULL)
			tree = ft_node_new(curr_f.name, ft_strlen(curr_f.name) + 1);
		else
			ft_node_add(tree, curr_f.name, ft_strlen(curr_f.name) + 1, f);
	}
	ft_treeprint(tree, options);
	free(curr_f.name);
	closedir(dir_p);
}
