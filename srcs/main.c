/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/21 13:45:59 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/stat.h>
#include <fcntl.h>

void	clean_up(t_input *input)
{
	del_structure_array(&(input->rooms));
	del_structure_array(&(input->links));
	if (input->line)
		free(input->line);
	ft_bzero(input, sizeof(*input));
}

bool	init_input_structure(t_input *input)
{
	input->line = NULL;
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

char	**copy_coords(t_array *rooms)
{
	char	**coords;
	size_t	i;
	char	*tmp;

	i = 0;
	coords = (char **)malloc(sizeof(char *) * rooms->nb_of_elements);
	if (!coords)
		return (NULL);
	while (i < rooms->nb_of_elements)
	{
		tmp = ft_strchr(rooms->array[i], ' ');
		*tmp = '\0';
		coords[i] = tmp + 1;
		i++;
	}
	return (coords);
}

bool	check_dups(char **arr, int size)
{
	while (size-- > 1)
	{
		if (ft_strequ(arr[size], arr[size - 1]) == 1)
			return (false);		
	}
	return (true);
}

bool	no_dups(t_array *rooms)
{
	char	**coords;
	
	coords = copy_coords(rooms);
	if (!coords)
		return (false);
	if (!sort_array(rooms->array, rooms->nb_of_elements)
		|| !sort_array(coords, rooms->nb_of_elements)
		|| !check_dups(rooms->array, rooms->nb_of_elements)
		|| !check_dups(coords, rooms->nb_of_elements))
	{
		free(coords);
		return (false);
	}
	free(coords);
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

	if (!init_input_structure(&input))
		return (-1);
	if (argc != 1)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	if (!read_input(&input, fd))
		ft_printf("Invalid\n");
	else
		ft_printf("Valid\n");
	if (fd != 0)
		close(fd);
	print_elements(&(input.rooms));
	print_elements(&(input.links));
	clean_up(&input);
	return (0);
}
