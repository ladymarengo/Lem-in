/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_without_sign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:38:46 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/02/03 18:11:46 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_digits(intmax_t ln)
{
	int	digits;

	digits = 1;
	while (ln / 10)
	{
		ln = ln / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa_without_sign(intmax_t n)
{
	char	*str;
	int		i;

	i = count_digits(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		if (n == INT64_MIN)
		{
			str[0] = '9';
			n = -223372036854775808;
		}
		n = -n;
	}
	while (n >= 10)
	{	
		str[i-- - 1] = '0' + (n % 10);
		n = n / 10;
	}
	str[i - 1] = '0' + n;
	return (str);
}
