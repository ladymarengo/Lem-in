/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:50:40 by jheiskan          #+#    #+#             */
/*   Updated: 2022/07/11 16:12:10 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	count_output_forks(t_data *data, int room)
{
	int	output_forks;
	
	output_forks = 0;
	while (room != data->start)
	{
		if (data->rooms[room].output->next != NULL)
			output_forks++;
		room = data->rooms[room].input->room;
	}
	return (output_forks);
}

void	delete_extra_output(t_data *data, int room, int best)
{
	t_list *tmp;

	tmp = data->rooms[room].input;
	while (tmp)
	{
		if (tmp->room != best)
			del_elem(&(data->rooms[tmp->room].output), room);
		tmp = tmp->next;
	}
}

bool	combine_lists(t_list **list, t_list *add)
{
	t_list *tmp;

	tmp = add;
	while (tmp)
	{
		if (!add_to_end(list, tmp->room))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

bool	check_input_forks(t_data *data, int room)
{
	int		best_room;
	int		best_output_forks;
	int		tmp_output_forks;
	t_list 	*tmp;

	best_output_forks = MAX_INT;
	best_room = -1;
	tmp = data->rooms[room].input;
	while (tmp)
	{
		tmp_output_forks = count_output_forks(data, tmp->room);
		if (tmp_output_forks < best_output_forks)
		{
			best_output_forks = tmp_output_forks;
			best_room = tmp->room;
		}
		tmp = tmp->next;
	}
	delete_extra_output(data, room, best_room);
	del_list(data->rooms[room].input);
	data->rooms[room].input = NULL;
	if (!add_to_start(&(data->rooms[room].input), best_room))
		return (false);
	return (true);
}

bool	del_input_forks(t_data *data)
{
	if (!combine_lists(&data->bfs.queue, data->rooms[data->start].output))
		return (false);
	while (data->bfs.queue)
	{
		data->bfs.current = pop_first_node(&data->bfs.queue);
		if (data->bfs.current == data->end)
			continue ;
		if (!check_input_forks(data, data->bfs.current))
			return (false);
		if (!combine_lists(&data->bfs.queue, data->rooms[data->bfs.current].output))
			return (false);
	}
	return (true);
	
}