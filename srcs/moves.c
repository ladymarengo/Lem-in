/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:13:46 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/08/04 13:51:28 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	count_paths(t_data *data)
{
	int		paths;
	t_list	*tmp;

	paths = 0;
	tmp = data->rooms[data->start].links;
	while (tmp)
	{
		if (data->bfs.new_conn[data->start][tmp->room] == FLOW)
			paths++;
		tmp = tmp->next;
	}
	return (paths);
}

bool	save_paths_lengths(t_data *data, int number_of_paths)
{
	int		length;
	t_list	*tmp;
	int		path;
	t_list	*links;

	tmp = data->rooms[data->start].links;
	while (tmp)
	{
		if (data->bfs.new_conn[data->start][tmp->room] == FLOW)
		{
			length = 1;
			path = tmp->room;
			while (path != data->end)
			{
				links = data->rooms[path].links;
				while (data->bfs.new_conn[path][links->room] != FLOW)
					links = links->next;
				length++;
				path = links->room;
			}
			data->bfs.path_lengths[--number_of_paths] = length;
		}
		tmp = tmp->next;
	}
	return (true);
}

void	sort_paths_lengths(t_data *data, int number_of_paths)
{
	int	first;
	int	second;
	int	tmp;

	first = 0;
	while (first < number_of_paths - 1)
	{
		second = 0;
		while (second < number_of_paths - first - 1)
		{
			if (data->bfs.path_lengths[second] \
				> data->bfs.path_lengths[second + 1])
			{
				tmp = data->bfs.path_lengths[second];
				data->bfs.path_lengths[second] \
					= data->bfs.path_lengths[second + 1];
				data->bfs.path_lengths[second + 1] = tmp;
			}
			second++;
		}
		first++;
	}
}

static bool	add_ants_on_path(t_data *data, int ant, int path, int sum)
{
	int	i;

	ant = 0;
	data->bfs.ant = (int *)ft_memalloc(sizeof(int) * data->bfs.number_of_paths);
	if (!data->bfs.ant)
		return (false);
	while (ant < data->ants)
	{
		path = 0;
		while (path < data->bfs.number_of_paths)
		{
			i = 0;
			sum = 0;
			while (i < path)
				sum += data->bfs.path_lengths[path] \
					- data->bfs.path_lengths[i++];
			if (data->ants - ant > sum)
			{
				data->bfs.ant[path]++;
				ant++;
			}
			path++;
		}
	}
	return (true);
}

int	count_turns(t_data *data)
{
	int	i;
	int	moves;

	data->bfs.number_of_paths = count_paths(data);
	if (data->bfs.path_lengths)
		free(data->bfs.path_lengths);
	data->bfs.path_lengths = (int *)malloc(sizeof(int) \
		* data->bfs.number_of_paths);
	if (!data->bfs.path_lengths)
		return (false);
	save_paths_lengths(data, data->bfs.number_of_paths);
	sort_paths_lengths(data, data->bfs.number_of_paths);
	if (!add_ants_on_path(data, 0, 0, 0))
		return (-1);
	moves = 0;
	i = 0;
	while (i < data->bfs.number_of_paths)
	{
		if (moves < data->bfs.path_lengths[i] + data->bfs.ant[i] - 1)
			moves = data->bfs.path_lengths[i] + data->bfs.ant[i] - 1;
		i++;
	}
	free(data->bfs.ant);
	data->bfs.ant = NULL;
	return (moves);
}
