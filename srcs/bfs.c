/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:19:50 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/15 12:46:59 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	init_bfs(t_data *data)
{
	int	i;

	i = 0;
	data->bfs.visited = (bool *)malloc(sizeof(bool) * data->number_of_rooms);
	if (!data->bfs.visited || !add_to_end(&data->bfs.queue, data->start))
		return (false);
	while (i < data->number_of_rooms)
		data->bfs.visited[i++] = false;
	data->bfs.visited[data->start] = true;
	data->rooms[data->start].bfs_level = 0;
	return (true);
}

bool	bfs(t_data *data)
{
	if (!init_bfs(data))
		return (false);
	while (data->bfs.queue)
	{
		data->bfs.current = pop_first_node(&data->bfs.queue);
		if (data->bfs.current == data->end)
			continue ;
		data->bfs.tmp = data->rooms[data->bfs.current].links;
		while (data->bfs.tmp)
		{
			data->bfs.link = data->bfs.tmp->room;
			if (data->rooms[data->bfs.link].bfs_level == -1)
				data->rooms[data->bfs.link].bfs_level = \
				data->rooms[data->bfs.current].bfs_level + 1;
			if (!data->bfs.visited[data->bfs.link])
			{
				data->bfs.visited[data->bfs.link] = true;
				if (!add_to_end(&data->bfs.queue, data->bfs.link))
					return (false);
			}
			data->bfs.tmp = data->bfs.tmp->next;
		}
	}
	return (true);
}

int	find_best(t_list *list, t_data *data, int current)
{
	int	best;

	best = current;
	while (list)
	{
		if (data->rooms[list->room].bfs_level < data->rooms[best].bfs_level
			&& data->rooms[list->room].bfs_level != -1)
			best = list->room;
		list = list->next;
	}
	return (best);
}

bool	save_shortest_path(t_data *data)
{
	int	current;

	if (data->rooms[data->end].bfs_level == -1)
		return (false);
	current = data->end;
	while (current != data->start)
	{
		if (!add_to_start(&data->shortest_path, current))
			return (false);
		current = find_best(data->rooms[current].links, data, current);
	}
	return (true);
}
