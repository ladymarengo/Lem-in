/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:38:07 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/08/04 12:25:21 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_coord_valid(char *line, int index)
{
	if (line[index] == '-')
		index++;
	if (!line[index] || line[index] == ' ')
		return (-1);
	while (line[index] && line[index] != ' ')
	{
		if (line[index] < '0' || line[index] > '9')
			return (-1);
		index++;
	}
	return (index);
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
	i = is_coord_valid(line, i);
	if (i < 0 || !line[i])
		return (false);
	i++;
	if (!line[i])
		return (false);
	i = is_coord_valid(line, i);
	if (i < 0 || line[i])
		return (false);
	return (true);
}

bool	is_link(char *line)
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
	input->flags.next_s = false;
	input->flags.next_e = false;
}
