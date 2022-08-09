/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:05 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/08/09 16:25:48 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	init_rooms(t_input *input, t_data *data)
{
	int	i;

	data->number_of_rooms = input->rooms.nb_of_elements;
	data->rooms = (t_room *)malloc(sizeof(t_room) * data->number_of_rooms);
	data->capacity = (int *)malloc(sizeof(int) * data->number_of_rooms);
	data->connections = \
		(t_connection **)malloc(sizeof(t_connection *) * data->number_of_rooms);
	if (!data->rooms || !data->capacity || !data->connections)
		return (false);
	i = 0;
	while (i < data->number_of_rooms)
	{
		data->capacity[i] = 0;
		data->connections[i] = (t_connection *)malloc(sizeof(t_connection) \
			* data->number_of_rooms);
		if (!data->connections[i])
			return (false);
		ft_bzero(data->connections[i], sizeof(t_connection) \
			* data->number_of_rooms);
		i++;
	}
	return (true);
}

void	init_room(t_input *input, t_data *data, int i)
{
	data->rooms[i].name = input->rooms.array[i];
	data->rooms[i].links = NULL;
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
	data->ants = (int) input->ants;
	return (true);
}
