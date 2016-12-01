/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:19:51 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 10:45:14 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		ft_ls_start(char *path,
		int (*f)(t_node *, const void *, const void *), int options)
{
	DIR				*dir_p;
	t_node			*buf;


}
