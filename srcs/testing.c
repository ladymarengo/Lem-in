/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:16:21 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/22 13:41:24 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	print_list(t_list *list)
{
	t_list *tmp;

	ft_printf("Printing list\n");
	while (list)
	{
		ft_printf("Element: %d\n", list->room);
		tmp = list->next;
		list = tmp;
	}
	return (false);
}

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

void	print_bfs_levels(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_rooms)
	{
		ft_printf("Room: %s, bfs level: %d\n", data->rooms[i].name, data->rooms[i].bfs_level);
		i++;
	}
}
