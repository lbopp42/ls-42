/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:50:31 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 14:48:46 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>

# define NB_FILTERS		4
# define FT_REVERSE 	0b000001
# define FT_TIME		0b000100
# define FT_TIME_REV	0b010000
# define FT_NAME		0b100000
# define FT_LONG		0b001000
# define FT_ALL			0b000010

typedef	struct s_node	t_node;
struct	s_node
{
	void		*content;
	size_t		content_size;
	t_node		*left;
	t_node		*right;
};

# include "filters.h"

void			ft_ls(char *path, int options);
void			ft_ls_start(char *path,
					int (*f)(t_node *, const void *, size_t), int options);

#endif
