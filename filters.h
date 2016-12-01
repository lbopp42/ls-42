/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:36:35 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/01 14:48:29 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTERS_H
# define FILTERS_H

# include "ft_ls.h"

int	filter_name(t_node *tree, const void *content, size_t content_size);
int	filter_name_rev(t_node *tree, const void *content, size_t content_size);
int	filter_time(t_node *tree, const void *content, size_t content_size);
int	filter_time_rev(t_node *tree, const void *content, size_t content_size);

#endif
