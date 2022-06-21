/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:05 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/21 16:54:26 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	init_rooms(t_input *input, t_data *data)
{
	data->number_of_rooms = input->rooms.nb_of_elements;
	data->rooms = (t_room *)malloc(sizeof(t_room) * data->number_of_rooms);
	if (!data->rooms)
		return (false);
	return (true);
}

bool	make_rooms(t_input *input, t_data *data)
{
	if (!init_rooms(input, data))
		return (false);
	parse_start_end(input, data);
	return (true);
}