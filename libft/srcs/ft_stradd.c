/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 09:34:15 by oyagci            #+#    #+#             */
/*   Updated: 2016/12/02 09:38:26 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_stradd(char *s1, char *s2)
{
	char *new;

	if (!(new = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	return (new);
}
