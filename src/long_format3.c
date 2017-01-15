/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 12:30:43 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/15 14:07:08 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

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
