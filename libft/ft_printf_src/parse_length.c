/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:26:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/02/08 16:23:13 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_length(char **format, t_tags *tags)
{
	size_t	i;

	if (ft_strncmp(*format, "hh", 2) == 0)
		tags->length = ft_strdup("hh");
	else if (ft_strncmp(*format, "h", 1) == 0)
		tags->length = ft_strdup("h");
	else if (ft_strncmp(*format, "ll", 2) == 0)
		tags->length = ft_strdup("ll");
	else if (ft_strncmp(*format, "l", 1) == 0)
		tags->length = ft_strdup("l");
	else if (ft_strncmp(*format, "L", 1) == 0)
		tags->length = ft_strdup("L");
	if (!(tags->length))
		error_exit(tags, 0);
	i = 0;
	while (i < ft_strlen(tags->length))
	{
		(*format)++;
		i++;
	}
}
