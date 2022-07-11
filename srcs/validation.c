/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:38:07 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/11 14:24:16 by jheiskan         ###   ########.fr       */
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
	if (line[0] == 'L' || line[0] == '#')
		return (false);
	while (line[i] != '-')
	{
		if (!line[i])
			return (false);
		i++;
	}
	if (!line[i + 1])
		return (false);
	return (true);
}

void	handle_start_end(t_input *input)
{
	if (input->flags.next_s)
		input->start = ft_strdup(input->rooms.array \
		[input->rooms.nb_of_elements - 1]);
	else if (input->flags.next_e)
		input->end = ft_strdup(input->rooms.array \
		[input->rooms.nb_of_elements - 1]);
	// add malloc protection
	input->flags.next_s = false;
	input->flags.next_e = false;
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
			handle_start_end(inp);
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
