/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:34:23 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/15 14:07:11 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#include <stdio.h>

void	print_perm(t_node *tree, const char *dir_path)
{
	char	*perm;
	acl_t	acl;

	if (!(perm = (char *)malloc(sizeof(char) * 12)))
		return ;
	ft_bzero(perm, 12);
	acl = acl_get_file(dir_path, ACL_TYPE_EXTENDED);
	perm[0] = S_ISBLK(tree->st.st_mode) ? 'b' : '-';
	S_ISCHR(tree->st.st_mode) ? perm[0] = 'c' : 0;
	S_ISDIR(tree->st.st_mode) ? perm[0] = 'd' : 0;
	S_ISLNK(tree->st.st_mode) ? perm[0] = 'l' : 0;
	S_ISSOCK(tree->st.st_mode) ? perm[0] = 's' : 0;
	S_ISFIFO(tree->st.st_mode) ? perm[0] = 'p' : 0;
	perm[1] = tree->st.st_mode & S_IRUSR ? 'r' : '-';
	perm[2] = tree->st.st_mode & S_IWUSR ? 'w' : '-';
	perm[3] = sticky_bits(tree->st, 1);
	perm[4] = tree->st.st_mode & S_IRGRP ? 'r' : '-';
	perm[5] = tree->st.st_mode & S_IWGRP ? 'w' : '-';
	perm[6] = sticky_bits(tree->st, 2);
	perm[7] = tree->st.st_mode & S_IROTH ? 'r' : '-';
	perm[8] = tree->st.st_mode & S_IWOTH ? 'w' : '-';
	perm[9] = sticky_bits(tree->st, 3);
	perm[10] = attr_acl(dir_path, tree->content->d_name);
	ft_putendsp(perm);
	free(perm);
}

void	print_nb_link(t_node *tree)
{
	char	*nb_link;

	nb_link = ft_itoa(tree->st.st_nlink);
	ft_putendsp(nb_link);
	free(nb_link);
}

void	print_uid(t_node *tree)
{
	ft_putendsp(getpwuid(tree->st.st_uid)->pw_name);
	print_space(g_size.max_user + 1, ft_strlen(getpwuid(tree->st.st_uid)->pw_name));
}

void	print_gr_id(t_node *tree)
{
	ft_putendsp(getgrgid(tree->st.st_gid)->gr_name);
	print_space(g_size.max_gr + 1, ft_strlen(getgrgid(tree->st.st_gid)->gr_name));
}

void	long_format(t_node *tree, const char *dir_path)
{
	char		*newpath;

	newpath = ft_strdup(dir_path);
	newpath = ft_stradd(newpath, "/");
	newpath = ft_stradd(newpath, tree->content->d_name);
	if (lstat(newpath, &tree->st) == -1)
	{
		free(newpath);
		return;
	}
	free(newpath);
	print_perm(tree, dir_path);
	print_space(g_size.max_nblink, ft_nbrlen(tree->st.st_nlink));
	print_nb_link(tree);
	print_uid(tree);
	print_gr_id(tree);
	print_size(tree);
	print_date(tree);
}
