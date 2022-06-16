/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 14:42:24 by nsamoilo         ###   ########.fr       */
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
	if (!read_input(&input, fd) || !check_input(&input))
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
