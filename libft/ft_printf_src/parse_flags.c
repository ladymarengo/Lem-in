/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:40:47 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/19 13:15:23 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_flag(char flag, t_tags *tags)
{
	if (flag == '+')
		tags->plus = 1;
	else if (flag == '-')
		tags->minus = 1;
	else if (flag == ' ')
		tags->space = 1;
	else if (flag == '0')
		tags->zero = 1;
	else if (flag == '#')
		tags->hash = 1;
}

int	is_flag(char flag)
{
	if (flag == '+' || flag == '-' || flag == '0'
		|| flag == '#' || flag == ' ')
		return (1);
	else
		return (0);
}

void	parse_flags(char **format, t_tags *tags)
{
	while (is_flag(**format))
	{
		add_flag(**format, tags);
		(*format)++;
	}
}
