/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:16:21 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/11 12:34:18 by nsamoilo         ###   ########.fr       */
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

void	print_rooms_links(t_data *data)
{
	int		i;
	t_list	*tmp;

	i = -1;
	while (++i < data->number_of_rooms)
	{
		if (data->rooms[i].bfs_level == -1)
			continue ;
		ft_printf("Room: %s. bfs_level is %d\n", data->rooms[i].name, data->rooms[i].bfs_level);
		tmp = data->rooms[i].links;
		ft_printf("All links:\n");
		while (tmp)
		{
			ft_printf("%s\n", data->rooms[tmp->room].name);
			tmp = tmp->next;
		}
		tmp = data->rooms[i].input;
		ft_printf("Input links:\n");
		while (tmp)
		{
			ft_printf("%s\n", data->rooms[tmp->room].name);
			tmp = tmp->next;
		}
		tmp = data->rooms[i].output;
		ft_printf("Output links:\n");
		while (tmp)
		{
			ft_printf("%s\n", data->rooms[tmp->room].name);
			tmp = tmp->next;
		}
		// i++;
	}
}
