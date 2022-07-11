/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:21:19 by jheiskan          #+#    #+#             */
/*   Updated: 2022/07/11 17:00:18 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	count_path(t_data *data, int room)
{
	int	path;
	
	path = 1;
	while (room != data->end)
	{
		path++;
		room = data->rooms[room].output->room;
	}
	return (path);
}

void	delete_extra_paths(t_data *data, int room, int best)
{
	t_list *tmp_link;
	t_list *tmp;

	tmp_link = data->rooms[room].output;
	while (tmp_link)
	{
		if (tmp_link->room != best)
		{
			data->rooms[tmp_link->room].bfs_level = -1;
			tmp = data->rooms[tmp_link->room].output;
			while (tmp->room != data->end)
			{
				data->rooms[tmp->room].bfs_level = -1;
				if (data->rooms[tmp->room].output->room == data->end)
					del_elem(&(data->rooms[data->end].input), tmp->room);
				tmp = data->rooms[tmp->room].output;
			}
		}	
		tmp_link = tmp_link->next;
	}
}

bool	check_output_forks(t_data *data, int room)
{
	int		best_room;
	int		best_path;
	int		tmp_path;
	t_list 	*tmp;

	if (!data->rooms[room].output->next)
		return (true);
	best_path = MAX_INT;
	best_room = -1;
	tmp = data->rooms[room].output;
	while (tmp)
	{
		tmp_path = count_path(data, tmp->room);
		if (tmp_path < best_path)
		{
			best_path = tmp_path;
			best_room = tmp->room;
		}
		tmp = tmp->next;
	}
	delete_extra_paths(data, room, best_room);
	del_list(data->rooms[room].output);
	data->rooms[room].output = NULL;
	if (!add_to_start(&(data->rooms[room].output), best_room))
		return (false);
	return (true);
}

bool	del_output_forks(t_data *data)
{
	if (!combine_lists(&data->bfs.queue, data->rooms[data->end].input))
		return (false);
	while (data->bfs.queue)
	{
		data->bfs.current = pop_first_node(&data->bfs.queue);
		if (data->bfs.current == data->start)
			continue ;
		if (!check_output_forks(data, data->bfs.current))
			return (false);
		if (!combine_lists(&data->bfs.queue, data->rooms[data->bfs.current].input))
			return (false);
	}
	return (true);
}