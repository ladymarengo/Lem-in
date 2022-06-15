/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/15 15:27:54 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/stat.h>
#include <fcntl.h>

void	put_room_to_list(char *line, bool start, bool end)
{
}

void	put_link_to_list(char *line)
{
}

bool	is_room_valid(char *line)
{
	return (true);
}

bool	is_link_valid(char *line)
{
	return (true);
}

bool	check_ants(char *line, int *ants)
{
	return (true);
}

bool	handle_commands(t_input_flags *flags, char *line)
{
	if (ft_strcmp("##start", line) == 0 && !flags->start && !flags->next_end)
	{
		flags->start = true;
		flags->next_start = true;
	}
	else if (ft_strcmp("##end", line) == 0 && !flags->end && !flags->next_start)
	{
		flags->end = true;
		flags->next_end = true;
	}
	else
		return (false);
	return (true);
}

int	read_input(int fd)
{
	char			*line;
	int				ants;
	t_array			*rooms;
	t_input_flags	flags;

	line = NULL;
	rooms = init_struct_array();
	ft_bzero(&flags, sizeof(flags));
	if (get_next_line(fd, &line) <= 0 || !check_ants(line, &ants))
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0 || ft_strcmp("##end", line) == 0)
		{
			if (!handle_commands(&flags, line))
				return (-1);
		}
		else if (!flags.parsing_links && is_room_valid(line))
		{
			if (!add_element(rooms, line))
				return (-1);
			flags.next_start = false;
			flags.next_end = false;
		}
		else if (is_link_valid(line))
		{
			put_link_to_list(line);
			flags.parsing_links = true;
		}
		else if (line[0] != '#')
			return (-1);
	}
	print_elements(rooms);
	del_structure_array(rooms);
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;
	
	if (argc != 1)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	if (read_input(fd) != 0)
		ft_printf("Invalid\n");
	else
		ft_printf("Valid\n");
	if (fd != 0)
		close(fd);
	return (0);
}
