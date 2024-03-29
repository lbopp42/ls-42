/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:26:56 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/12 17:48:22 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size(char const *s, int start)
{
	int i;

	i = start;
	while (s[i])
		i++;
	while ((s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t') && (i > 0))
	{
		i--;
	}
	if ((i - start) < 0)
		return (0);
	else
		return (i - start);
}

static char		*ft_news(const char *s, int start, int len, char *news)
{
	int i;

	i = 0;
	while (start < len)
	{
		news[i] = s[start];
		start++;
		i++;
	}
	news[i] = '\0';
	return (news);
}

char			*ft_strtrim(char const *s)
{
	char	*news;
	int		i;
	int		start;
	int		j;
	int		size;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = i;
	size = ft_size(s, start);
	if (!(news = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	news = ft_news(s, start, size + start, news);
	return (news);
}
