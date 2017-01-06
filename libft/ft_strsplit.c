/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:27:12 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/12 15:27:38 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			word++;
		}
		while (s[i] != c && s[i + 1] != '\0' && s[i])
			i++;
		i++;
	}
	return (word);
}

static	char	**ft_fill(char const *s, char **array, char c)
{
	int i;
	int letter;
	int word;

	i = 0;
	word = 0;
	while (s[i])
	{
		letter = 0;
		while (s[i] != c && s[i])
		{
			array[word][letter] = s[i];
			letter++;
			i++;
		}
		array[word][letter] = '\0';
		while (s[i] == c && s[i])
			i++;
		word++;
	}
	array[word] = 0;
	return (array);
}

static	char	**ft_letter(char const *s, char c, char **array)
{
	int i;
	int letter;
	int word;

	i = 0;
	word = 0;
	while (s[i])
	{
		letter = 0;
		while (s[i] != c && s[i])
		{
			letter++;
			i++;
		}
		while (s[i] == c && s[i])
			i++;
		if (!(array[word] = (char*)malloc(sizeof(char) * (letter + 1))))
			return (NULL);
		word++;
	}
	return (array);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		word;
	char	**array;

	i = 0;
	word = 0;
	if (!(s))
		return (NULL);
	if (!(s = ft_strtrimchar(s, c)))
		return (0);
	if (!(array = (char**)malloc(sizeof(char*) * (ft_word(s, c) + 1))))
		return (0);
	if (!(array = ft_letter(s, c, array)))
		return (0);
	return (ft_fill(s, array, c));
}
