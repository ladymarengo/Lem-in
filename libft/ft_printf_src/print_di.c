/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:52:11 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/02/07 15:55:03 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_int_sign(t_tags *tags, char **str, intmax_t number)
{
	char	*temp;

	temp = NULL;
	if (number < 0)
	{
		temp = ft_strjoin("-", *str);
		free(*str);
		*str = temp;
	}
	else if (number >= 0 && (tags->plus == 1 || tags->space == 1))
	{
		if (tags->plus == 1)
			temp = ft_strjoin("+", *str);
		else if (tags->space == 1)
			temp = ft_strjoin(" ", *str);
		free(*str);
		*str = temp;
	}
	if (!(*str))
		error_exit(tags, 0);
}

void	handle_i_precision(t_tags *tags, char **str, intmax_t number, int add)
{
	char	*add_str;
	char	*temp;

	if (tags->precision >= 0)
	{
		add = tags->precision - ft_strlen(*str);
		if (add > 0)
		{
			add_str = ft_strnew(add);
			if (!add_str)
				error_exit(tags, 1, *str);
			ft_memset(add_str, '0', add);
			temp = ft_strjoin(add_str, *str);
			free(*str);
			free(add_str);
			*str = temp;
		}
		if (tags->precision == 0 && number == 0)
		{
			free(*str);
			*str = ft_strdup("");
		}
		if (!(*str))
			error_exit(tags, 0);
	}
}

void	print_di(t_tags *tags, va_list args, int *chars)
{
	intmax_t	number;
	char		*str;

	if (ft_strcmp(tags->length, "hh") == 0)
		number = (signed char)va_arg(args, int);
	else if (ft_strcmp(tags->length, "h") == 0)
		number = (short)va_arg(args, int);
	else if (ft_strcmp(tags->length, "ll") == 0)
		number = (long long)va_arg(args, long long);
	else if (ft_strcmp(tags->length, "l") == 0)
		number = (long)va_arg(args, long);
	else
		number = (int)va_arg(args, int);
	str = ft_itoa_without_sign(number);
	if (!str)
		error_exit(tags, 0);
	handle_i_precision(tags, &str, number, 0);
	add_int_sign(tags, &str, number);
	print_left_or_right(&str, tags, chars);
}
