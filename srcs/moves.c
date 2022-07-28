/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:13:46 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/28 14:10:24 by nsamoilo         ###   ########.fr       */
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

static int	lengths_sum(int *paths, int current)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (i < current)
	{
		sum += paths[current] - paths[i];
		i++;
	}
	return (sum);
}

bool	save_paths_lengths(t_data *data, int number_of_paths)
{
	int		length;
	t_list	*tmp;
	int		path;
	t_list	*links;

	data->bfs.path_lengths = (int *)malloc(sizeof(int) * number_of_paths);
	if (!data->bfs.path_lengths)
		return (false);
	tmp = data->rooms[data->start].links;
	while (tmp)
	{
		if (data->bfs.new_conn[data->start][tmp->room] == FLOW)
		{
			length = 1;
			path = tmp->room;
			number_of_paths--;
			while (path != data->end)
			{
				links = data->rooms[path].links;
				while (data->bfs.new_conn[path][links->room] != FLOW)
					links = links->next;
				length++;
				path = links->room;
			}
			data->bfs.path_lengths[number_of_paths] = length;
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

int	count_turns(t_data *data)
{
	int	paths;
	int	ant;
	int	path;
	int	*ants;
	int	moves;

	paths = count_paths(data);
	data->bfs.number_of_paths = paths;
	save_paths_lengths(data, paths);
	sort_paths_lengths(data, paths);
	ants = (int *)malloc(sizeof(int) * paths);
	ft_bzero(ants, sizeof(int) * paths);
	ant = 0;
	while (ant < data->ants)
	{
		path = 0;
		while (path < paths)
		{
			if (data->ants - ant > lengths_sum(data->bfs.path_lengths, path))
			{
				ants[path]++;
				ant++;
			}
			path++;
		}
	}
	// for (int i = 0; i < paths; i++)
	// 	ft_printf("\nPath %d length %d ants %d\n", i, data->bfs.path_lengths[i], ants[i]);
	moves = 0;
	for (int i = 0; i < paths; i++)
	{
		if (moves < data->bfs.path_lengths[i] + ants[i] - 1)
			moves = data->bfs.path_lengths[i] + ants[i] - 1;
	}
	// ft_printf("Moves: %d\n", moves);
	return (moves);
}
