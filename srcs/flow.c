/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:08:19 by jheiskan          #+#    #+#             */
/*   Updated: 2022/07/28 14:09:31 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	copy_connection_and_capacity(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->number_of_rooms)
	{
		data->capacity[x] = data->bfs.tmp_capacity[x];
		y = 0;
		while (y < data->number_of_rooms)
		{
			data->connections[x][y] = data->bfs.new_conn[x][y];
			y++;
		}
		x++;
	}
	data->number_of_paths = data->bfs.number_of_paths;
}

bool	init_tmp_arrays(t_data *data)
{
	int	x;
	int	y;

	data->bfs.tmp_capacity = (int *)malloc(sizeof(int) * data->number_of_rooms);
	data->bfs.new_conn = \
		(t_connection **)malloc(sizeof(t_connection *) * data->number_of_rooms);
	if (!data->bfs.tmp_capacity || !data->bfs.new_conn)
		return (false);
	x = 0;
	while (x < data->number_of_rooms)
	{
		data->bfs.tmp_capacity[x] = data->capacity[x];
		data->bfs.new_conn[x] = (t_connection *)
			malloc(sizeof(t_connection) * data->number_of_rooms);
		if (!data->bfs.new_conn[x])
			return (false);
		y = 0;
		while (y < data->number_of_rooms)
		{
			data->bfs.new_conn[x][y] = data->connections[x][y];
			y++;
		}
		x++;
	}
	return (true);
}

bool	init_bfs(t_data *data)
{
	int	i;

	i = 0;
	if (!data->bfs.visited)
		data->bfs.visited = (bool *)malloc(sizeof(bool) * data->number_of_rooms);
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

bool better_moves(t_data *data)
{
	int new_moves;

	new_moves = count_turns(data);
	if (new_moves < data->moves)
	{
		data->moves = new_moves;
		return (true);
	}
	return (false);
}

void update_connections(t_data *data)
{
	int room;

	room = data->end;
	while (room != data->start)
	{
		if (data->bfs.new_conn[room][data->bfs.parents[room]] == FLOW)
			data->bfs.new_conn[room][data->bfs.parents[room]] = NO_FLOW;
		else
		{
			data->bfs.new_conn[data->bfs.parents[room]][room] = FLOW;
			data->bfs.tmp_capacity[room]++;
		}
		room = data->bfs.parents[room];
	}
}

bool solve(t_data *data)
{
	t_return	ret;

	if (!init_tmp_arrays(data))
		return (false);
	while (true)
	{
		if (!init_bfs(data))
			return (false);
		ret = bfs(data);
		if (ret == FAIL)
			return (false);
		else if (ret == NO_PATH)
			return (true);
		else
		{
			update_connections(data);
			if (better_moves(data))
				copy_connection_and_capacity(data);
			else
				return (true);
			// ft_printf("Next try:\n");
		}
	}
	return (false);
}
