/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 08:55:45 by oyagci            #+#    #+#             */
/*   Updated: 2016/11/12 13:40:54 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <libft.h>

static int	ft_get_nb_digits(int n)
{
	int				nb_digits;

	nb_digits = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		nb_digits += 1;
	}
	return (nb_digits);
}

static int	ft_pow(int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

static char	*ft_stradd(char *dst, char const *src)
{
	char	*str;

	if (!(str = ft_strjoin(src, dst)))
		return (NULL);
	free(dst);
	return (str);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				nb_digits;
	unsigned int	abs;
	int				i;

	nb_digits = ft_get_nb_digits(n);
	if (n < 0)
		str = ft_strnew(nb_digits + 1);
	else
		str = ft_strnew(nb_digits);
	if (str == NULL)
		return (NULL);
	abs = ft_abs(n);
	i = 0;
	while (i < nb_digits)
	{
		str[i] = ((abs / ft_pow(10, nb_digits - i - 1)) % 10) + '0';
		i++;
	}
	if (n < 0)
		str = ft_stradd(str, "-");
	return (str);
}
