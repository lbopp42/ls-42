/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:07:33 by oyagci            #+#    #+#             */
/*   Updated: 2016/11/08 15:26:33 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static char	*ft_strctrim(const char *s, char c)
{
	int		len;
	char	*str;
	char	*s_cpy;

	s_cpy = (char *)s;
	len = ft_strlen(s_cpy);
	while (*s_cpy == c)
	{
		len--;
		s_cpy++;
	}
	while (s_cpy[len - 1] == c)
		len -= 1;
	if (len < 0)
		len = 0;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_strlcat(str, s_cpy, len + 1);
	return (str);
}

static int	ft_word_count(char const *s, char c)
{
	int word_count;
	int i;

	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			word_count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word_count);
}

static int	ft_write_word(char **dst, char **s, char c)
{
	size_t	len;

	len = 0;
	while (**s == c && *s != '\0')
		(*s)++;
	while ((*s)[len] != c && (*s)[len] != '\0')
		len += 1;
	if (len == 0)
	{
		*dst = (char *)malloc(sizeof(char));
		dst = 0;
	}
	if (!(*dst = ft_strnew(len)))
		return (0);
	ft_strncpy(*dst, *s, len);
	*s += len;
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	char	*str;
	int		word_count;
	int		i;

	if (!s || !(str = ft_strctrim(s, c)))
		return (NULL);
	word_count = ft_word_count(s, c);
	if (!(split = (char **)malloc(sizeof(char *) * word_count + 1)))
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		if (!(ft_write_word(&split[i], &str, c)))
			return (NULL);
		i += 1;
	}
	split[i] = 0;
	return (split);
}
