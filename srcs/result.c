/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:13:46 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/26 16:38:45 by nsamoilo         ###   ########.fr       */
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
		if (data->bfs.tmp_connections[data->start][tmp->room] == FLOW)
			paths++;
		tmp = tmp->next;
	}
	return (paths);
}

// bool	save_paths(t_data *data, int number_of_paths)
// {
// 	int		path;
// 	t_list	*tmp;
// 	t_list	*path_tmp;

// 	data->paths = (t_path *)malloc(sizeof(t_path) * number_of_paths);
// 	// add malloc protection
// 	path = 0;
// 	tmp = data->rooms[data->start].output;
// 	while (tmp)
// 	{
// 		data->paths[path].ants = 0;
// 		data->paths[path].length = 0;
// 		data->paths[path].path = NULL;
// 		path_tmp = tmp;
// 		while (path_tmp)
// 		{
// 			data->paths[path].length++;
// 			add_to_end(&data->paths[path].path, path_tmp->room);
// 			path_tmp = data->rooms[path_tmp->room].output;
// 		}
// 		// ft_printf("Path %d length %d\n", path, data->paths[path].length);
// 		tmp = tmp->next;
// 		path++;
// 	}
// 	return (true);
// }

// void	sort_paths(t_data *data, int number_of_paths)
// {
// 	int		path;
// 	int		second;
// 	// int		tmp_length;
// 	// t_list	*tmp_path;
// 	t_path 	tmp;

// 	path = 0;
// 	while (path < number_of_paths - 1)
// 	{
// 		second = 0;
// 		while (second < number_of_paths - path - 1)
// 		{
// 			if (data->paths[second].length > data->paths[second + 1].length)
// 			{
// 				// tmp_length = data->paths[path].length;
// 				// tmp_path = data->paths[path].path;
// 				// data->paths[path].length = data->paths[path + 1].length;
// 				// data->paths[path].path = data->paths[path + 1].path;
// 				// data->paths[path + 1].length = tmp_length;
// 				// data->paths[path + 1].path = tmp_path;
// 				tmp = data->paths[second];
// 				data->paths[second] = data->paths[second + 1];
// 				data->paths[second + 1] = tmp;
// 			}
// 			second++;
// 		}
// 		path++;
// 	}
// }

int	lengths_sum(int	*paths, int current)
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
		if (data->bfs.tmp_connections[data->start][tmp->room] == FLOW)
		{
			length = 1;
			path = tmp->room;
			number_of_paths--;
			while (path != data->end)
			{
				links = data->rooms[path].links;
				while (data->bfs.tmp_connections[path][links->room] != FLOW)
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
			if (data->bfs.path_lengths[second] > data->bfs.path_lengths[second + 1])
			{
				tmp = data->bfs.path_lengths[second];
				data->bfs.path_lengths[second] = data->bfs.path_lengths[second + 1];
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
			// ft_printf("sum %d\n", lengths_sum(data->paths, path));
			if (data->ants - ant > lengths_sum(data->bfs.path_lengths, path))
			{
				ants[path]++;
				ant++;
			}
			path++;
		}
	}
	for (int i = 0; i < paths; i++)
		ft_printf("\nPath %d length %d ants %d\n", i, data->bfs.path_lengths[i], ants[i]);
	moves = 0;
	for (int i = 0; i < paths; i++)
	{
		if (moves < data->bfs.path_lengths[i] + ants[i] - 1)
			moves = data->bfs.path_lengths[i] + ants[i] - 1;
	}
	ft_printf("Moves: %d\n", moves);
	return (moves);
}
