/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 13:06:15 by jheiskan         ###   ########.fr       */
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

int	read_input(t_input *input, int fd)
{
	if (get_next_line(fd, &(input->line)) <= 0 || !check_ants(input->line, &(input->ants)))
		return (-1);
	while (get_next_line(fd, &(input->line)) > 0)
	{
		if (ft_strcmp("##start", input->line) == 0 || ft_strcmp("##end", input->line) == 0)
		{
			if (!handle_commands(&(input->flags), input->line))
				return (-1);
		}
		else if (!input->flags.parsing_links && is_room_valid(input->line))
		{
			if (!add_element(&(input->rooms), input->line))
				return (-1);
			input->flags.next_start = false;
			input->flags.next_end = false;
		}
		else if (is_link_valid(input->line) && !input->flags.next_start && !input->flags.next_end)
		{
			input->flags.parsing_links = true;
		}
		else if (input->line[0] != '#' || input->flags.next_start || input->flags.next_end)
			return (-1);
	}
	print_elements(&(input->rooms));
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_input	input;
	
	if (!init_input_structure(&input))
		return (-1);
	if (argc != 1)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	if (read_input(&input, fd) != 0)
		ft_printf("Invalid\n");
	else
		ft_printf("Valid\n");
	if (fd != 0)
		close(fd);
	clean_up(&input);
	return (0);
}
