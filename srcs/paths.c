/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:18:08 by jheiskan          #+#    #+#             */
/*   Updated: 2022/08/04 13:08:49 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_paths(t_data *data)
{
	int		path;
	int		second;
	t_path	tmp;

	path = 0;
	while (path < data->number_of_paths - 1)
	{
		second = 0;
		while (second < data->number_of_paths - path - 1)
		{
			if (data->paths[second].length > data->paths[second + 1].length)
			{
				tmp = data->paths[second];
				data->paths[second] = data->paths[second + 1];
				data->paths[second + 1] = tmp;
			}
			second++;
		}
		path++;
	}
}

bool	save_path(t_data *data, int room, int i)
{
	t_list	*tmp;

	data->paths[i].path = NULL;
	data->paths[i].ants = 0;
	data->paths[i].length = 1;
	if (!add_to_start(&(data->paths[i].path), data->start))
		return (false);
	while (room != data->end)
	{
		if (!add_to_end(&(data->paths[i].path), room))
			return (false);
		tmp = data->rooms[room].links;
		while (tmp)
		{
			if (data->connections[room][tmp->room] == FLOW)
				room = tmp->room;
			tmp = tmp->next;
		}
		data->paths[i].length++;
	}
	if (!add_to_end(&(data->paths[i].path), room))
		return (false);
	return (true);
}

bool	save_paths(t_data *data)
{
	t_list	*tmp;
	int		i;

	data->paths = (t_path *)malloc(sizeof(t_path) * data->number_of_paths);
	if (!data->paths)
		return (false);
	tmp = data->rooms[data->start].links;
	i = 0;
	while (tmp)
	{
		if (data->connections[data->start][tmp->room] == FLOW
			&& !save_path(data, tmp->room, i++))
			return (false);
		tmp = tmp->next;
	}
	sort_paths(data);
	return (true);
}

void	print_paths(t_data *data)
{
	t_list	*tmp;
	int		i;

	i = 0;
	ft_printf("Printing paths\n");
	while (i < data->number_of_paths)
	{
		tmp = data->paths[i].path;
		ft_printf("Path %d (length %d): ", i, data->paths[i].length);
		while (tmp)
		{
			ft_printf("%s ", data->rooms[tmp->room].name);
			tmp = tmp->next;
		}
		ft_printf("\n");
		i++;
	}
	ft_putendl("");
}
