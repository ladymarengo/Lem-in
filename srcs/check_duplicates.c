/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:28:47 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/21 15:30:49 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**copy_coords(t_array *rooms)
{
	char	**coords;
	size_t	i;
	char	*tmp;

	i = 0;
	coords = (char **)malloc(sizeof(char *) * rooms->nb_of_elements);
	if (!coords)
		return (NULL);
	while (i < rooms->nb_of_elements)
	{
		tmp = ft_strchr(rooms->array[i], ' ');
		*tmp = '\0';
		coords[i] = tmp + 1;
		i++;
	}
	return (coords);
}

bool	check_dups(char **arr, int size)
{
	while (size-- > 1)
	{
		if (ft_strequ(arr[size], arr[size - 1]) == 1)
			return (false);
	}
	return (true);
}

bool	no_dups(t_array *rooms)
{
	char	**coords;

	coords = copy_coords(rooms);
	if (!coords)
		return (false);
	if (!sort_array(rooms->array, rooms->nb_of_elements)
		|| !sort_array(coords, rooms->nb_of_elements)
		|| !check_dups(rooms->array, rooms->nb_of_elements)
		|| !check_dups(coords, rooms->nb_of_elements))
	{
		free(coords);
		return (false);
	}
	free(coords);
	return (true);
}
