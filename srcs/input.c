/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:24:49 by jheiskan          #+#    #+#             */
/*   Updated: 2022/08/04 12:25:55 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	check_input(t_input *inp)
{
	while (get_next_line(inp->fd, &(inp->line)) > 0)
	{
		if (!add_element(&(inp->map), inp->line))
			return (false);
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
		else if (is_link(inp->line) && !inp->flags.next_s && !inp->flags.next_e)
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
	if (!input->start || !input->end)
		return (false);
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
