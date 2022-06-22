/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:05 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/22 12:10:54 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_room(t_room *room)
{
	del_list(room->links);
	del_list(room->input);
	del_list(room->output);
}

bool	init_rooms(t_input *input, t_data *data)
{
	data->number_of_rooms = input->rooms.nb_of_elements;
	data->rooms = (t_room *)malloc(sizeof(t_room) * data->number_of_rooms);
	if (!data->rooms)
		return (false);
	return (true);
}

void	init_room(t_input *input, t_data *data, int i)
{
	data->rooms[i].name = input->rooms.array[i];
	if (i == data->start)
		data->rooms[i].start = true;
	if (i == data->end)
		data->rooms[i].end = true;
	data->rooms[i].links = NULL;
	data->rooms[i].input = NULL;
	data->rooms[i].output = NULL;
	data->rooms[i].bfs_level = -1;
}

bool	make_rooms(t_input *input, t_data *data)
{
	int	i;

	if (!init_rooms(input, data))
		return (false);
	parse_start_end(input, data);
	i = 0;
	while (i < data->number_of_rooms)
	{
		init_room(input, data, i);
		i++;
	}
	if (!parse_links(input, data))
		return (false);
	return (true);
}