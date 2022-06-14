/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:19:40 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/02/03 18:15:37 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_precision(char **format, t_tags *tags)
{
	if (**format == '.')
	{
		(*format)++;
		tags->precision = ft_atoi(*format);
		while (**format >= '0' && **format <= '9')
			(*format)++;
	}
}
