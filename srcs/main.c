/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 12:20:19 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/stat.h>
#include <fcntl.h>


bool	is_room_valid(char *line)
{
	int	i;

	i = 0;
	if (line[0] == 'L' || line[0] == '#')
		return (false);
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i++])
		return (false);
	while (line[i] != ' ')
	{
		if (!line[i] || line[i] < '0' || line[i] > '9')
			return (false);
		i++;
	}
	i++;
	if (!line[i])
		return (false);
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	is_link_valid(char *line)
{
	int	i;

	i = 0;	
	while (line[i] != '-')
	{
		if (!line[i] || line[i] < '0' || line[i] > '9')
			return (false);
		i++;
	}
	i++;
	if (!line[i])
		return (false);
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	check_ants(char *line, long int *ants)
{
	while (*line)
	{
		if (!(*line) || *line < '0' || *line > '9')
			return (false);
		*ants *= 10;
		*ants += *line - '0';
		line++;
	}
	ft_printf("ants: %ld\n", *ants);
	if (*ants < 1 || *ants > MAX_INT)
		return (false);
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
	long int		ants;
	t_array			*rooms;
	t_input_flags	flags;

	line = NULL;
	ants = 0;
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
		else if (is_link_valid(line) && !flags.next_start && !flags.next_end)
		{
			flags.parsing_links = true;
		}
		else if (line[0] != '#' || flags.next_start || flags.next_end)
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
