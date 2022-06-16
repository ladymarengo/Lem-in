/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:40:49 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 14:41:06 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	check_ants(char *line, long int *ants)
{
	while (*line)
	{
		if (!(*line) || *line < '0' || *line > '9')
			return (false);
		*ants *= 10;
		*ants += *line - '0';
		line++;
	}
	ft_printf("ants: %ld\n", *ants);
	if (*ants < 1 || *ants > MAX_INT)
		return (false);
	return (true);
}
