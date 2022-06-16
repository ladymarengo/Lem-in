/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:38:07 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 14:40:07 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

bool	read_input(t_input *input, int fd)
{
	if (get_next_line(fd, &(input->line)) <= 0 || !check_ants(input->line, &(input->ants)))
		return (false);
	while (get_next_line(fd, &(input->line)) > 0)
	{
		if (ft_strcmp("##start", input->line) == 0 || ft_strcmp("##end", input->line) == 0)
		{
			if (!handle_commands(&(input->flags), input->line))
				return (false);
		}
		else if (!input->flags.parsing_links && is_room_valid(input->line))
		{
			if (!add_element(&(input->rooms), input->line))
				return (false);
			input->flags.next_start = false;
			input->flags.next_end = false;
		}
		else if (is_link_valid(input->line) && !input->flags.next_start && !input->flags.next_end)
		{
			if (!add_element(&(input->links), input->line))
				return (false);
			input->flags.parsing_links = true;
		}
		else if (input->line[0] != '#' || input->flags.next_start || input->flags.next_end)
			return (false);
	}
	return (true);
}

bool	check_input(t_input *input)
{
	if (!input->flags.start || !input->flags.end
		|| input->links.nb_of_elements == 0)
		return (false);
	return (true);
}
