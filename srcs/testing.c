/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:16:21 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/26 15:23:09 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	print_list(t_list *list)
{
	t_list *tmp;

	ft_printf("\nPrinting list\n");
	while (list)
	{
		ft_printf("Element: %d\n", list->room);
		tmp = list->next;
		list = tmp;
	}
	return (false);
}

bool	print_path(t_data *data, int room)
{
	t_list *tmp;

	tmp = data->rooms[room].output;
	ft_printf("\nPrinting path\n%s - %s", data->rooms[data->start].name, data->rooms[room].name);
	while (tmp && tmp->room != data->end)
	{
		ft_printf(" - %s", data->rooms[tmp->room].name);
		tmp = data->rooms[tmp->room].output;
	}
	ft_printf(" - %s\n", data->rooms[data->end].name);
	return (false);
}

void	print_paths(t_data *data)
{
	t_list *tmp;

	tmp = data->rooms[data->start].output;

	while (tmp)
	{
		print_path(data, tmp->room);
		tmp = tmp->next;
	}
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
		ft_printf("Room: %s. bfs_level is %d index: %d\n", data->rooms[i].name, data->rooms[i].bfs_level, i);
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

void	print_connections(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	ft_printf("%6s", "");
	while (x < data->number_of_rooms)
		ft_printf("%6s", data->rooms[x++].name);
	ft_printf("\n");
	x = 0;
	while (x < data->number_of_rooms)
	{
		y = 0;
		ft_printf("%6s", data->rooms[x].name);
		while (y < data->number_of_rooms)
		{
			if (data->connections[x][y] == NO_CONNECTION)
				ft_printf("%6s", "");
			else if (data->connections[x][y] == NO_FLOW)
				ft_printf("%6s", ".");
			else
				ft_printf("%6s", "*");
			y++;
		}
		ft_printf("\n");
		x++;
	}
	ft_printf("\n");
}