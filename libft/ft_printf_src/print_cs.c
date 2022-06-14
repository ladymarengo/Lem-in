/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:34:27 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/02/07 12:55:05 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(t_tags *tags, va_list args, int *chars)
{
	char	*c;

	c = ft_strnew(1);
	if (!c)
		error_exit(tags, 0);
	c[0] = (char)va_arg(args, int);
	print_left_or_right(&c, tags, chars);
}

void	print_s(t_tags *tags, va_list args, int *chars)
{
	char	*s;
	char	*temp;

	s = (char *)va_arg(args, char *);
	if (s == NULL)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(s);
	if (!s)
		error_exit(tags, 0);
	if (tags->precision >= 0)
	{
		temp = ft_strsub(s, 0, tags->precision);
		free(s);
		s = temp;
	}
	if (!s)
		error_exit(tags, 0);
	print_left_or_right(&s, tags, chars);
}
