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
	int			i;
	t_bfs_path	*path;

	i = 0;
	if (!data->bfs.visited)
		data->bfs.visited = (bool *)malloc(sizeof(bool) \
			* data->number_of_rooms);
	else
		ft_bzero(data->bfs.visited, sizeof(bool) * data->number_of_rooms);
	while (data->bfs.queue_path)
	{
		path = data->bfs.queue_path;
		data->bfs.queue_path = data->bfs.queue_path->next;
		del_list(path->path);
		free(path);
	}
	del_list(data->bfs.current_path);
	data->bfs.queue_path = NULL;
	if (!data->bfs.visited || !add_to_end_path(&(data->bfs.queue_path), NULL, data->start))
		return (false);
	while (i < data->number_of_rooms)
		data->bfs.visited[i++] = false;
	data->bfs.visited[data->start] = true;
	return (true);
}

bool	valid_path(t_data *data)
{
	if ((data->bfs.visited[data->bfs.link] && data->bfs.new_conn[data->bfs.link][data->bfs.current] == NO_FLOW)
		|| data->bfs.new_conn[data->bfs.current][data->bfs.link] == FLOW)
		return (false);
	if (data->bfs.tmp_capacity[data->bfs.current] > 0
		&& data->bfs.new_conn[data->bfs.link][data->bfs.current] == NO_FLOW
		&& data->bfs.new_conn[data->bfs.current] \
			[data->bfs.current_path->next->room] == NO_FLOW)
		return (false);
	return (true);
}

t_return	bfs(t_data *data)
{
	while (data->bfs.queue_path)
	{
		data->bfs.current_path = pop_first_node_path(&data->bfs.queue_path);
		data->bfs.current = data->bfs.current_path->room;
		if (data->bfs.current_path->room == data->end)
			return (NEW_PATH);
		data->bfs.tmp = data->rooms[data->bfs.current_path->room].links;
		while (data->bfs.tmp)
		{
			data->bfs.link = data->bfs.tmp->room;
			if (valid_path(data))
			{
				data->bfs.visited[data->bfs.link] = true;
				if (!add_to_end_path(&data->bfs.queue_path, data->bfs.current_path, data->bfs.link))
					return (FAIL);
			}
			data->bfs.tmp = data->bfs.tmp->next;
		}
		del_list(data->bfs.current_path);
	}
	return (NO_PATH);
}
