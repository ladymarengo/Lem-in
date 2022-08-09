/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:08:19 by jheiskan          #+#    #+#             */
/*   Updated: 2022/08/09 12:01:06 by jheiskan         ###   ########.fr       */
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

bool	better_moves(t_data *data)
{
	int	new_moves;

	new_moves = count_turns(data);
	if (new_moves < data->moves)
	{
		data->moves = new_moves;
		return (true);
	}
	return (false);
}

void	update_connections(t_data *data)
{
	int		room;
	t_list	*path;

	path = data->bfs.current_path;
	room = path->room;
	while (room != data->start)
	{
		if (data->bfs.new_conn[room][path->next->room] == FLOW)
			data->bfs.new_conn[room][path->next->room] = NO_FLOW;
		else
		{
			data->bfs.new_conn[path->next->room][room] = FLOW;
			data->bfs.tmp_capacity[room]++;
		}
		path = path->next;
		room = path->room;
	}
}

bool	solve(t_data *data)
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
		}
	}
	return (false);
}
