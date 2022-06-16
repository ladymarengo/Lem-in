/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:16:21 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 15:16:34 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_elements(t_array *array)
{
	size_t	i;

	i = 0;
	ft_printf("Number of elements: %u\nSize of array: %u\n", \
		array->nb_of_elements, array->size);
	while (i < array->nb_of_elements)
		ft_printf("%s\n", array->array[i++]);
	ft_putchar('\n');
}
