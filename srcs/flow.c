/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:08:19 by jheiskan          #+#    #+#             */
/*   Updated: 2022/07/26 13:21:04 by jheiskan         ###   ########.fr       */
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
			data->connections[x][y] = data->bfs.tmp_connections[x][y];
			y++;
		}
		x++;
	}
	
}

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
	data->bfs.tmp_capacity = (int *)malloc(sizeof(int) * data->number_of_rooms);
	data->bfs.tmp_connections = (t_connection **)malloc(sizeof(t_connection *) * data->number_of_rooms);
	if (!data->bfs.tmp_capacity || !data->bfs.tmp_connections)
		return (false);
	i = 0;
	while (i < data->number_of_rooms)
	{
		data->bfs.tmp_connections[i] = (t_connection *)malloc(sizeof(t_connection) * data->number_of_rooms);
		if (!data->bfs.tmp_connections[i])
			return (false);
		ft_bzero(data->bfs.tmp_connections[i], sizeof(t_connection) * data->number_of_rooms);
		i++;
	}
	return (true);
}

bool	solve(t_data *data)
{
	
}