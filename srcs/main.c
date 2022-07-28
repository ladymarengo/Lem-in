/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/28 12:32:17 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/stat.h>
#include <fcntl.h>

void	clean_up(t_input *input, t_data *data)
{
	del_structure_array(&(input->rooms));
	del_structure_array(&(input->links));
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

bool	init_input_structure(t_input *input)
{
	input->line = NULL;
	input->start = NULL;
	input->end = NULL;
	input->ants = 0;
	if (!init_struct_array(&(input->rooms)))
		return (false);
	if (!init_struct_array(&(input->links)))
	{
		del_structure_array(&(input->rooms));
		return (false);
	}
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
	return (true);
}

bool	read_input(t_input *input, int fd)
{
	if (get_next_line(fd, &(input->line)) <= 0
		|| !check_ants(input->line, &(input->ants)))
		return (false);
	if (!check_input(input, fd) || !post_input_check(input)
		|| !no_dups(&(input->rooms)))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_input	input;
	t_data	data;

	data.shortest_path = NULL;
	if (!init_input_structure(&input) || !init_data_structure(&data))
		return (-1);
	if (argc != 1)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	if (!read_input(&input, fd) || !make_rooms(&input, &data))
		ft_printf("ERROR\n");
	else
	{
		data.ants = (int) input.ants;
		solve(&data);
		//print_connections(&data);
		print_result(&data, &input);
	}
	if (fd != 0)
		close(fd);
	clean_up(&input, &data);
	return (0);
}
