/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:50:31 by oyagci            #+#    #+#             */
/*   Updated: 2016/11/30 16:19:33 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>

# define FT_REVERSE 0b0001
# define FT_ALL		0b0010

typedef	struct s_btree	t_btree;
struct	s_btree
{
	void		*content;
	t_btree		*left;
	t_btree		*right;
};

typedef	struct s_file	t_file;
struct	s_file
{
	char			*name;
	struct stat		st;
	struct passwd	pw;
	struct group	grp;
};

#endif
