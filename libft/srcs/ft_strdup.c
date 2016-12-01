/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:14:19 by oyagci            #+#    #+#             */
/*   Updated: 2016/11/05 11:27:27 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*s;
	size_t	len;

	len = ft_strlen(s1) + 1;
	if (!(s = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(s, s1);
	return (s);
}
