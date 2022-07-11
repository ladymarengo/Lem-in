/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:22:05 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/11 12:08:48 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	delete_useless_links(t_data *data)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < data->number_of_rooms)
	{
		if (data->rooms[i].bfs_level != -1)
		{
			tmp = data->rooms[i].links;
			while (tmp)
			{
				if (data->rooms[tmp->room].bfs_level == -1
					|| data->rooms[tmp->room].bfs_level == data->rooms[i].bfs_level)
					{
						tmp = tmp->next;
						continue ;
					}
				if (!((data->rooms[tmp->room].bfs_level < data->rooms[i].bfs_level
							&& add_to_start(&(data->rooms[i].input), tmp->room))
						|| (data->rooms[tmp->room].bfs_level
							> data->rooms[i].bfs_level
							&& add_to_start(&(data->rooms[i].output), tmp->room))))
					return (false);
				tmp = tmp->next;
			}
		}
		del_list(data->rooms[i].links);
		data->rooms[i].links = NULL;
		i++;
	}
	return (true);
}

bool	update_links(t_data *data)
{
	data->rooms[data->end].bfs_level = MAX_INT;
	delete_useless_links(data);
	return (true);
}