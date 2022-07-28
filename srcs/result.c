/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:18:08 by jheiskan          #+#    #+#             */
/*   Updated: 2022/07/28 13:20:52 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_paths(t_data *data)
{
	int		path;
	int		second;
	t_path 	tmp;

	path = 0;
	while (path < data->number_of_paths - 1)
	{
		second = 0;
		while (second < data->number_of_paths - path - 1)
		{
			if (data->paths[second].length > data->paths[second + 1].length)
			{
				tmp = data->paths[second];
				data->paths[second] = data->paths[second + 1];
				data->paths[second + 1] = tmp;
			}
			second++;
		}
		path++;
	}
}

bool	save_path(t_data *data, int room, int i)
{
	t_list	*tmp;
	
	data->paths[i].path = NULL;
	data->paths[i].ants = 0;
	data->paths[i].length = 1;
	if (!add_to_start(&(data->paths[i].path), data->start))
		return (false);
	while (room != data->end)
	{
		if (!add_to_end(&(data->paths[i].path), room))
			return (false);
		tmp = data->rooms[room].links;
		while (tmp)
		{
			if (data->connections[room][tmp->room] == FLOW)
				room = tmp->room;
			tmp = tmp->next;
		}
		//room = tmp->room;
		data->paths[i].length++;
	}
	if (!add_to_end(&(data->paths[i].path), room))
		return (false);
	return (true);
}

bool	save_paths(t_data *data)
{
	t_list	*tmp;
	int		i;
	
	data->paths = (t_path *)malloc(sizeof(t_path) * data->number_of_paths);
	if (!data->paths)
		return (false);
	tmp = data->rooms[data->start].links;
	i = 0;
	while (tmp)
	{
		if (data->connections[data->start][tmp->room] == FLOW
			&& !save_path(data, tmp->room, i++))
			return (false);	
		tmp = tmp->next;
	}
	return (true);
}

static int	lengths_sum(t_data *data, int current)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (i < current)
	{
		sum += data->paths[current].length - data->paths[i].length;
		i++;
	}
	return (sum);
}

bool	print_result(t_data *data, t_input *input)
{
	t_list	**ants;
	int		nb_of_ants;
	bool	moving;
	int		path;
	int		i;
	int		line_number;
	
	(void)input;
	if (data->number_of_paths == 0)
		return (false);
	save_paths(data);
	sort_paths(data);
	print_paths(data);
	ants = (t_list **)malloc(sizeof(t_list *) * data->ants);
	if (!ants)
		return (false);
	nb_of_ants = 0;
	moving = true;
	line_number = 1;
	while (moving)
	{
		path = 0;
		while (path < data->number_of_paths)
		{
			if (data->ants - nb_of_ants > lengths_sum(data, path))
			{
				ants[nb_of_ants] = data->paths[path].path;
				nb_of_ants++;
			}
			path++;
		}
		i = 0;
		moving = false;
		if (true) // need to add flag handling
			ft_printf("%3d: ", line_number++);
		while (i < nb_of_ants)
		{
			if (ants[i])
			{
				ants[i] = ants[i]->next;
				if (ants[i])
				{
					if (moving)
						ft_printf(" ");
					ft_printf("L%d-%s", i + 1, data->rooms[ants[i]->room].name);
					moving = true;
				}
			}
			i++;
		}
		if (moving)
			ft_printf("\n");
		else if (true)
			ft_printf("END\n");
	}
	//Print map here

	return (true);
}