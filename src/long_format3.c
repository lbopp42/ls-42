/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 12:30:43 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:44:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	attr_acl(const char *path, char *name)
{
	size_t	xattr;
	acl_t	acl;
	char	*newpath;

	newpath = ft_strdup(path);
	newpath = ft_stradd(newpath, "/");
	newpath = ft_stradd(newpath, name);
	xattr = 0;
	acl = acl_get_file(newpath, ACL_TYPE_EXTENDED);
	xattr = listxattr(newpath, NULL, 0, XATTR_NOFOLLOW);
	free(newpath);
	if (xattr > 0)
	{
		acl_free((void*)acl);
		return ('@');
	}
	else if (acl)
	{
		acl_free((void*)acl);
		return ('+');
	}
	else
		return (' ');
}

int		nb_col(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
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
