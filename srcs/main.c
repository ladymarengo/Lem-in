/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/28 14:43:33 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/stat.h>
#include <fcntl.h>

void	clean_up(t_input *input, t_data *data)
{
	del_structure_array(&(input->rooms));
	del_structure_array(&(input->links));
	del_structure_array(&(input->map));
	if (input->line)
		free(input->line);
	if (input->start)
		free(input->start);
	if (input->end)
		free(input->end);
	ft_bzero(input, sizeof(*input));
	while (data->number_of_rooms-- > 0)
		del_room(&data->rooms[data->number_of_rooms]);
	free(data->rooms);
	free(data->capacity);
	del_list(data->shortest_path);
	del_list(data->bfs.queue);
	if (data->bfs.visited)
		free(data->bfs.visited);
}

void	cleanup_and_exit(t_input *input, t_data *data, int ret, char *message)
{
	ft_printf("%s\n", message);
	clean_up(input, data);
	exit(ret);
}

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
	data->bfs.queue = NULL;
	data->bfs.visited = NULL;
	data->bfs.parents = NULL;
	data->bfs.path_lengths = NULL;
	data->bfs.tmp = NULL;
	data->number_of_paths = 0;
	data->print_lines = false;
	data->print_paths = false;
	return (true);
}

bool	read_input(t_input *input)
{
	if (get_next_line(input->fd, &(input->line)) <= 0
		|| !check_ants(input->line, &(input->ants)))
		return (false);
	if (!add_element(&(input->map), input->line))
		return (false);
	if (!check_input(input) || !post_input_check(input)
		|| !no_dups(&(input->rooms)))
		return (false);
	return (true);
}

void	handle_args(t_data *data, t_input *input, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-file") == 0 && i + 1 < argc)
			input->fd = open(argv[i + 1], O_RDONLY);
		else if (ft_strcmp(argv[i], "-lines") == 0)
			data->print_lines = true;
		else if (ft_strcmp(argv[i], "-paths") == 0)
			data->print_paths = true;
		else if (ft_strcmp(argv[i], "-help") == 0)
			cleanup_and_exit(input, data, 0, USAGE);
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
	// if (argc != 1)
	// 	fd = open(argv[1], O_RDONLY);
	// else
	// 	fd = 0;
	if (!read_input(&input) || !make_rooms(&input, &data))
		ft_printf("ERROR\n");
	else
	{
		data.ants = (int) input.ants;
		solve(&data);
		//print_connections(&data);
		print_result(&data, &input);
	}
	// if (fd != 0)
	// 	close(fd);
	clean_up(&input, &data);
	return (0);
}
