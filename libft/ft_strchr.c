/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:01:47 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 15:36:25 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;
	char	*p;

	p = (char *)s;
	index = 0;
	while (p[index])
	{
		if (p[index] == c)
			return (&(p[index]));
		index++;
	}
	return (NULL);
}
