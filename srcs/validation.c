/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:38:07 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 15:14:22 by nsamoilo         ###   ########.fr       */
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
	if (ft_strcmp("##start", line) == 0 && !flags->start && !flags->next_e)
	{
		flags->start = true;
		flags->next_s = true;
	}
	else if (ft_strcmp("##end", line) == 0 && !flags->end && !flags->next_s)
	{
		flags->end = true;
		flags->next_e = true;
	}
	else
		return (false);
	return (true);
}

bool	check_input(t_input *inp, int fd)
{
	while (get_next_line(fd, &(inp->line)) > 0)
	{
		if (!ft_strcmp("##start", inp->line) || !ft_strcmp("##end", inp->line))
		{
			if (!handle_commands(&(inp->flags), inp->line))
				return (false);
		}
		else if (!inp->flags.parsing_links && is_room_valid(inp->line))
		{
			if (!add_element(&(inp->rooms), inp->line))
				return (false);
			inp->flags.next_s = false;
			inp->flags.next_e = false;
		}
		else if (is_link_valid(inp->line)
			&& !inp->flags.next_s && !inp->flags.next_e)
		{
			if (!add_element(&(inp->links), inp->line))
				return (false);
			inp->flags.parsing_links = true;
		}
		else if (inp->line[0] != '#' || inp->flags.next_s || inp->flags.next_e)
			return (false);
	}
	return (true);
}

bool	post_input_check(t_input *input)
{
	if (!input->flags.start || !input->flags.end
		|| input->links.nb_of_elements == 0)
		return (false);
	return (true);
}
