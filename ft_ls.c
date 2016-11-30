/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:19:51 by oyagci            #+#    #+#             */
/*   Updated: 2016/11/30 16:42:52 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"

void			ft_ls(char *path, int options)
{
	DIR				*dir_p;
	t_list			*f_list;
	t_file			f_buf;
	struct dirent	*curr_ent;

	f_list = NULL;
	if (!(dir_p = opendir(path)))
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		return ;
	}
	while ((curr_ent = readdir(dir_p)) != NULL)
	{
		f_buf.name = ft_strjoin("", curr_ent->d_name);
	}
}

int		ft_filetime_cmp(const t_file *file1, const t_file *file2)
{
	if (file1->st.st_mtimespec.tv_nsec < file2->st.st_mtimespec.tv_nsec)
		return (1);
	else if (file1->st.st_mtimespec.tv_nsec > file2->st.st_mtimespec.tv_nsec)
		return (-1);
	else
		return (0);
}

void	ft_btreeput_filter(t_btree *tree, t_file *file,
		int (*f)(const t_file *, const t_file *))
{
	if (tree->left != NULL)
		ft_btreeput_filter(tree->left, file, f);
	if (f(file, (t_file *)tree->content) < 0)
	{
		tree->left = file;
		return ;
	}
	if (tree->right != NULL)
		ft_btreeput_filter(tree->right, file, f);
	if (f(file, (t_file *)tree->content) >= 0)
		tree->right = file;
}
