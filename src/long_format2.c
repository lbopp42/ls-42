/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:19:59 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/15 14:07:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_space(int	nb_space, int len)
{
	while (len < nb_space)
	{
		write(1, " ", 1);
		len++;
	}
}

void	print_size(t_node *tree)
{
	if (S_ISCHR(tree->st.st_mode) ||
			S_ISBLK(tree->st.st_mode))
	{
		print_space(g_size.max_major, ft_nbrlen(major(tree->st.st_rdev)));
		ft_putnbr(major(tree->st.st_rdev));
		write(1, ", ", 2);
		print_space(g_size.max_minor, ft_nbrlen(minor(tree->st.st_rdev)));
		ft_putnbr(minor(tree->st.st_rdev));
	}
	else
	{
		if (g_size.max_minor + g_size.max_major > g_size.max_size)
			print_space(g_size.max_minor + g_size.max_major + 2
					, ft_nbrlen(tree->st.st_size));
		else
			print_space(g_size.max_size, ft_nbrlen(tree->st.st_size));
		ft_putnbr(tree->st.st_size);
	}
	write(1, " ", 1);
}

void	print_date(t_node *tree)
{
	char	*date;
	size_t	len;
	char	*tmp;
	char	*tmp2;

	if (time(NULL) - tree->st.st_mtimespec.tv_sec > 15778799 ||
			time(NULL) - tree->st.st_mtimespec.tv_sec < 0)
	{
		len = ft_strlen(ft_strchr(ctime(&tree->st.st_mtimespec.tv_sec),
		' ') + 1) - ft_strlen(ft_strchr(
			ctime(&tree->st.st_mtimespec.tv_sec), ':')) - 3;
		if (!(date = (char*)malloc(sizeof(char) * len + 1)))
			return ;
		ft_bzero(date, len + 1);
		date = ft_strncpy(date, ft_strchr(ctime(
				&tree->st.st_mtimespec.tv_sec), ' ') + 1, len);
		tmp = ft_strrchr(ctime(&tree->st.st_mtimespec.tv_sec), ' ');
		tmp2 = ft_strcdup(tmp, '\n');
		date = ft_stradd(date, " ");
		date = ft_stradd(date, tmp2);
		free(tmp2);
	}
	else
	{
		len = ft_strlen(ft_strchr(ctime(
						&tree->st.st_mtimespec.tv_sec), ' ') + 1) - ft_strlen(
					ft_strrchr(ctime(&tree->st.st_mtimespec.tv_sec), ':'));
		if (!(date = (char*)malloc(sizeof(char) * len + 1)))
			return ;
		ft_bzero(date, len + 1);
		date = ft_strncpy(date, ft_strchr(ctime(
						&tree->st.st_mtimespec.tv_sec), ' ') + 1, len);
	}
	ft_putendsp(date);
	free(date);
}

void	print_total(t_node *tree)
{
	int	total;

	total = 0;
	while (tree != NULL)
	{
		total = total + tree->st.st_blocks;
		tree = tree->next_dir;
	}
	ft_putendsp("total");
	ft_putnbr(total);
	write(1, "\n", 1);
}

char	sticky_bits(struct stat st, int mode)
{
	if (mode == 1)
	{
		if (st.st_mode & S_ISUID)
			return ((st.st_mode & S_IXUSR) ? 's' : 'S');
		else
			return ((st.st_mode & S_IXUSR) ? 'x' : '-');
	}
	if (mode == 2)
	{
		if (st.st_mode & S_ISGID)
			return ((st.st_mode & S_IXGRP) ? 's' : 'S');
		else
			return ((st.st_mode & S_IXGRP) ? 'x' : '-');
	}
	if (mode == 3)
	{
		if (st.st_mode & S_ISVTX)
			return ((st.st_mode & S_IXOTH) ? 't' : 'T');
		else
			return ((st.st_mode & S_IXOTH) ? 'x' : '-');
	}
	return (0);
}
