/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:54:57 by jheiskan          #+#    #+#             */
/*   Updated: 2022/08/04 13:55:32 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	init_bfs(t_data *data)
{
	int	i;

	i = 0;
	if (!data->bfs.visited)
		data->bfs.visited = (bool *)malloc(sizeof(bool) \
			* data->number_of_rooms);
	else
		ft_bzero(data->bfs.visited, sizeof(bool) * data->number_of_rooms);
	if (!data->bfs.parents)
		data->bfs.parents = (int *)malloc(sizeof(int) * data->number_of_rooms);
	else
		ft_bzero(data->bfs.parents, sizeof(int) * data->number_of_rooms);
	del_list(data->bfs.queue);
	data->bfs.queue = NULL;
	if (!data->bfs.visited || !add_to_end(&data->bfs.queue, data->start))
		return (false);
	while (i < data->number_of_rooms)
		data->bfs.visited[i++] = false;
	i = 0;
	while (i < data->number_of_rooms)
		data->bfs.parents[i++] = -1;
	data->bfs.visited[data->start] = true;
	data->rooms[data->start].bfs_level = 0;
	return (true);
}

bool	valid_path(t_data *data)
{
	if (data->bfs.visited[data->bfs.link]
		|| data->bfs.new_conn[data->bfs.current][data->bfs.link] == FLOW)
		return (false);
	if (data->bfs.tmp_capacity[data->bfs.current] > 0
		&& data->bfs.new_conn[data->bfs.link][data->bfs.current] == NO_FLOW
		&& data->bfs.new_conn[data->bfs.current] \
			[data->bfs.parents[data->bfs.current]] == NO_FLOW)
		return (false);
	return (true);
}

t_return	bfs(t_data *data)
{
	while (data->bfs.queue)
	{
		data->bfs.current = pop_first_node(&data->bfs.queue);
		if (data->bfs.current == data->end)
			return (NEW_PATH);
		data->bfs.tmp = data->rooms[data->bfs.current].links;
		while (data->bfs.tmp)
		{
			data->bfs.link = data->bfs.tmp->room;
			if (valid_path(data))
			{
				data->bfs.visited[data->bfs.link] = true;
				data->bfs.parents[data->bfs.link] = data->bfs.current;
				if (!add_to_end(&data->bfs.queue, data->bfs.link))
					return (FAIL);
			}
			data->bfs.tmp = data->bfs.tmp->next;
		}
	}
	return (NO_PATH);
}
