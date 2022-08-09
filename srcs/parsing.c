/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:40:49 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/08/09 13:24:38 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	if (*ants < 1 || *ants > MAX_INT)
		return (false);
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

void	parse_start_end(t_input *input, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < input->rooms.nb_of_elements)
	{
		if (ft_strcmp(input->rooms.array[i], input->start) == 0)
		{
			data->start = i;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < input->rooms.nb_of_elements)
	{
		if (ft_strcmp(input->rooms.array[i], input->end) == 0)
		{
			data->end = i;
			break ;
		}
		i++;
	}
}
