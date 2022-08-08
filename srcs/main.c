/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/08/04 15:24:17 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/stat.h>
#include <fcntl.h>

bool	init_input_structure(t_input *input)
{
	input->line = NULL;
	input->start = NULL;
	input->end = NULL;
	input->ants = 0;
	input->fd = 0;
	if (!init_struct_array(&(input->rooms))
		|| !init_struct_array(&(input->links))
		|| !init_struct_array(&(input->map)))
		return (false);
	ft_bzero(&(input->flags), sizeof(input->flags));
	return (true);
}

bool	init_data_structure(t_data *data)
{
	data->ants = 0;
	data->moves = MAX_INT;
	data->number_of_rooms = 0;
	data->rooms = NULL;
	data->shortest_path = NULL;
	data->paths = NULL;
	data->bfs.queue_path = NULL;
	data->bfs.current_path = NULL;
	data->bfs.visited = NULL;
	data->bfs.path_lengths = NULL;
	data->bfs.tmp = NULL;
	data->bfs.ant = NULL;
	data->connections = NULL;
	data->bfs.new_conn = NULL;
	data->capacity = NULL;
	data->bfs.tmp_capacity = NULL;
	data->number_of_paths = 0;
	data->print_lines = false;
	data->print_paths = false;
	data->ants_on_path = NULL;
	return (true);
}

void	handle_args(t_data *data, t_input *input, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-file") == 0)
		{
			if (i + 1 < argc)
				input->fd = open(argv[i++ + 1], O_RDONLY);
			else
				cleanup_and_exit(input, data, 0, USAGE);
			if (input->fd < 0)
				cleanup_and_exit(input, data, 0, "Can't open file\n");
		}
		else if (ft_strcmp(argv[i], "-lines") == 0)
			data->print_lines = true;
		else if (ft_strcmp(argv[i], "-paths") == 0)
			data->print_paths = true;
		else if (ft_strcmp(argv[i], "-help") == 0)
			cleanup_and_exit(input, data, 0, USAGE);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_data	data;

	data.shortest_path = NULL;
	if (!init_input_structure(&input) || !init_data_structure(&data))
		cleanup_and_exit(&input, &data, -1, "Malloc error");
	if (argc != 1)
		handle_args(&data, &input, argv, argc);
	if (!read_input(&input) || !make_rooms(&input, &data) || !solve(&data) \
		|| !print_result(&data, &input))
		cleanup_and_exit(&input, &data, -1, "ERROR\n");
	cleanup_and_exit(&input, &data, 0, NULL);
	return (0);
}
