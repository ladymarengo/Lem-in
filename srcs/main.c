/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:00 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/14 15:11:01 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	store_start_end(char *line)
{
	if (get_next_line(0, &line) <= 0 || !is_room_valid(line))
		return (-1);
	else
		list_room(line);
}

void	read_input(void)
{
	char	*line;
	int		ants;
	
	if (get_next_line(0, &line) <= 0 || !check_ants(line, &ants))
		return (-1);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0)
		{
			store_start_end(line);
		}
				
			
	}
}

int	main(void)
{
	read_input();
	
	return (0);
}
