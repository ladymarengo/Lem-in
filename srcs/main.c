/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/14 16:17:25 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int	read_input(void)
{
	char	*line;
	int		ants;
	bool	start;
	bool	end;
	bool	parsing_links;

	start = false;
	end = false;
	parsing_links = false;
	if (get_next_line(0, &line) <= 0 || !check_ants(line, &ants))
		return (-1);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0 && ft_strcmp("##end", line) == 0)
		{
			if (ft_strcmp("##start", line) == 0)
				start = true;
			if (ft_strcmp("##end", line) == 0)
				end = true;
		}
		else if (!parsing_links && is_room_valid(line))
		{
			put_room_to_list(line, start, end);
			start = false;
			end = false;
		}
		else if (is_link_valid(line))
		{
			put_link_to_list(line);
			parsing_links = true;
		}
		else if (line[0] != '#')
			return (-1);
	}
	return (0);
}

int	main(void)
{
	if (read_input() != 0)
		ft_printf("Invalid\n");
	else
		ft_printf("Valid\n");
	
	return (0);
}
