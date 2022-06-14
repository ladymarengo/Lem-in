/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_poux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:39:55 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/02/08 11:19:55 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_u_precision(t_tags *tags, char **str, uintmax_t number, int add)
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
	}
}

char	*create_string(t_tags *tags, uintmax_t number)
{
	char	*str;

	str = NULL;
	if (tags->specifier == 'u')
		str = ft_itoa_base(number, 10);
	else if (tags->specifier == 'o')
		str = ft_itoa_base(number, 8);
	else if (ft_tolower(tags->specifier) == 'x' || tags->specifier == 'p')
		str = ft_itoa_base(number, 16);
	if (tags->specifier == 'X')
		ft_str_toupper(str);
	if (!str)
		error_exit(tags, 0);
	return (str);
}

void	print_poux(t_tags *tags, va_list args, int *chars)
{
	uintmax_t	number;
	char		*str;

	if (ft_strcmp(tags->length, "hh") == 0)
		number = (unsigned char)va_arg(args, unsigned int);
	else if (ft_strcmp(tags->length, "h") == 0)
		number = (unsigned short)va_arg(args, unsigned int);
	else if (ft_strcmp(tags->length, "ll") == 0 || tags->specifier == 'p')
		number = (unsigned long long)va_arg(args, unsigned long long);
	else if (ft_strcmp(tags->length, "l") == 0)
		number = (unsigned long)va_arg(args, unsigned long);
	else
		number = (unsigned int)va_arg(args, unsigned int);
	str = create_string(tags, number);
	handle_u_precision(tags, &str, number, 0);
	if (!str)
		error_exit(tags, 0);
	print_left_or_right(&str, tags, chars);
}
