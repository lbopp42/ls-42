/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btreemain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 08:55:34 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/06 10:24:23 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char	*perm(t_node *tree)
{
	char	*perm;

	if (!(perm = (char*)malloc(sizeof(char) * 11)))
		return (0);
	perm[0] = S_ISBLK(tree->content->st.st_mode) ? 'b' : '-';
	S_ISCHR(tree->content->st.st_mode) ? perm[0] = 'c' : 0;
	S_ISDIR(tree->content->st.st_mode) ? perm[0] = 'd' : 0;
	S_ISLNK(tree->content->st.st_mode) ? perm[0] = 'l' : 0;
	S_ISSOCK(tree->content->st.st_mode) ? perm[0] = 's' : 0;
	S_ISFIFO(tree->content->st.st_mode) ? perm[0] = 'p' : 0;
	perm[1] = tree->content->st.st_mode & S_IRUSR ? 'r' : '-';
	perm[2] = tree->content->st.st_mode & S_IWUSR ? 'w' : '-';
	perm[3] = tree->content->st.st_mode & S_IXUSR ? 'x' : '-';
	perm[4] = tree->content->st.st_mode & S_IRGRP ? 'r' : '-';
	perm[5] = tree->content->st.st_mode & S_IWGRP ? 'w' : '-';
	perm[6] = tree->content->st.st_mode & S_IXGRP ? 'x' : '-';
	perm[7] = tree->content->st.st_mode & S_IROTH ? 'r' : '-';
	perm[8] = tree->content->st.st_mode & S_IWOTH ? 'w' : '-';
	perm[9] = tree->content->st.st_mode & S_IXOTH ? 'x' : '-';
	return (perm);
}

int	total_blocks(t_node *tree)
{
	int total;

	total = 0;
	while (tree != NULL)
	{
		total = total + tree->content->st.st_blocks;
		tree = tree->brother;
	}
	return (total);
}

/*t_len	*align_in_column(t_node *tree)
{
	t_len	*len_max;

	if (!(len_max = (t_len*)malloc(sizeof(t_len))))
		return (NULL);
	len_max->link = 0;
	len_max->user = 0;
	len_max->group = 0;
	len_max->filesize = 0;
	while (tree != NULL)
	{
		if (len_max->link < ft_nbrlen(tree->content->st.st_nlink))
			len_max->link = ft_nbrlen(tree->content->st.st_nlink);
		if ((size_t)len_max->user < ft_strlen(tree->content->pass->pw_name))
			len_max->user = ft_strlen(tree->content->pass->pw_name);
		if ((size_t)len_max->group < ft_strlen(tree->content->gr->gr_name))
			len_max->group = ft_strlen(tree->content->gr->gr_name);
		if (len_max->filesize < ft_nbrlen(tree->content->st.st_size))
			len_max->filesize = ft_nbrlen(tree->content->st.st_size);
		tree = tree->brother;
	}
	return (len_max);
}*/

void	print_long(t_node *tree)
{
	char	*date;
	size_t	len;

	ft_putendsp(perm(tree));
	ft_putendsp(ft_itoa(tree->content->st.st_nlink));
	ft_putendsp(tree->content->pass->pw_name);
	ft_putendsp(tree->content->gr->gr_name);
	if (S_ISCHR(tree->content->st.st_mode) || S_ISBLK(tree->content->st.st_mode))
	{
		printf("%d, ", major(tree->content->st.st_rdev)); //TODO
		ft_putendsp(ft_itoa(minor(tree->content->st.st_rdev)));
	}
	else
		ft_putendsp(ft_itoa(tree->content->st.st_size));
	if (time(NULL) - tree->content->st.st_mtimespec.tv_sec > 15778799)
	{
		len = ft_strlen(ft_strchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ' ') + 1) - ft_strlen(ft_strchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ':')) - 3;
		if (!(date = (char*)malloc(sizeof(char) * len)))
			return;
		ft_bzero(date, len);
		date = ft_strncpy(date,
			ft_strchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ' ') + 1, len);
		date = ft_stradd(date, " ");
		date = ft_stradd(date, ft_strcdup(ft_strrchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ' '), '\n'));
	}
	else
	{
		len = ft_strlen(ft_strchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ' ') + 1)
			- ft_strlen(ft_strrchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ':'));
		if (!(date = (char*)malloc(sizeof(char) * len)))
			return;
		ft_bzero(date, len);
		date = ft_strncpy(date,
			ft_strchr(ctime(&tree->content->st.st_mtimespec.tv_sec), ' ') + 1, len);
	}
	ft_putendsp(date);
}

void	print_brother_tree(t_node *tree, const char *path, int *i)
{
	char	*newpath;

	newpath = NULL;
	if ((g_multi == 1 && *i != 1) || (g_option & LS_RECUR && *i != 1))
		write(1, "\n", 1);
	if (g_multi == 1 || *i != 1)
	{
		if (strcmp(g_path, "/") == 0)
			newpath = ft_strdup(path + 1);
		else
			newpath = ft_strdup(path);
		ft_putendl(ft_strjoin(newpath, ":"));
	}
	if (g_option & LS_LONG)
		ft_putendl(ft_strjoin("total ", ft_itoa(total_blocks(tree))));
	while (tree != NULL)
	{
		if (tree->content->info->d_type == DT_DIR && ft_strcmp(tree->content->info->d_name, ".") != 0 && ft_strcmp(tree->content->info->d_name, "..") != 0)
		{
			if (g_option & LS_LONG)
				print_long(tree);
			ft_putendl(tree->content->info->d_name);
		}
		else
		{
			if (g_option & LS_LONG)
				print_long(tree);
			ft_putendl(tree->content->info->d_name);
		}
		tree = tree->brother;
	}
}

void	dir_tree(t_node *tree, const char *path)
{
	char		*newpath;

	while (tree != NULL)
	{
		if (tree->content->info->d_type == DT_DIR && ft_strcmp(tree->content->info->d_name, ".") != 0 && ft_strcmp(tree->content->info->d_name, "..") != 0)
		{
			newpath = ft_strjoin(path, "/");
			tree->child = put_in_tree(tree->child, ft_stradd(newpath, tree->content->info->d_name));
		}
		tree = tree->brother;
	}
}

#include <stdio.h>

t_node	*put_in_tree(t_node *tree, const char *path)
{
	DIR				*dir;
	struct dirent	*lecture;
	static int		i = 0;

	if (!(dir = opendir(path)))
		ft_putendl(ft_strjoin("ft_ls: ", ft_stradd(ft_strjoin((char*)path, ": "), strerror(errno))));
	else
	{
		i++;
		while ((lecture = readdir(dir)))
		{
			if (lecture->d_name[0] == '.')
			{
				if (g_option & LS_ALL)
				{
					if (g_option & LS_TIME)
						new_node(&tree, lecture, &cmp_time, path);
					else
						new_node(&tree, lecture, &cmp, path);
				}
			}
			else if (g_option & LS_TIME)
			{
				new_node(&tree, lecture, &cmp_time, path);
			}
			else
				new_node(&tree, lecture, &cmp, path);
		}
		closedir(dir);
		print_brother_tree(tree, path, &i);
		if (g_option & LS_RECUR)
			dir_tree(tree, path);
	}
	return (tree);
}
