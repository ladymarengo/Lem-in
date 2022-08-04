/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:16:21 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/08/04 13:08:42 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	lengths_sum(t_data *data, int current)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (i < current)
	{
		sum += data->paths[current].length - data->paths[i].length;
		i++;
	}
	return (sum);
}

void	print_elements(t_array *array)
{
	size_t	i;

	i = 0;
	while (i < array->nb_of_elements)
		ft_printf("%s\n", array->array[i++]);
	ft_putchar('\n');
}

void	add_ants_on_path(t_data *data, int *nb_of_ants)
{
	int	path;

	path = 0;
	while (path < data->number_of_paths)
	{
		if (data->ants - *nb_of_ants > lengths_sum(data, path))
		{
			data->ants_on_path[*nb_of_ants] = data->paths[path].path;
			(*nb_of_ants)++;
		}
		path++;
	}
}

void	print_moves(t_data *data, int *nb_of_ants, bool *moving, int *line)
{
	int	i;

	i = 0;
	*moving = false;
	if (data->print_lines)
		ft_printf("%3d: ", (*line)++);
	while (i < *nb_of_ants)
	{
		if (data->ants_on_path[i] && data->ants_on_path[i]->next)
		{
			data->ants_on_path[i] = data->ants_on_path[i]->next;
			if (*moving)
				ft_printf(" ");
			ft_printf("L%d-%s", i + 1, \
				data->rooms[data->ants_on_path[i]->room].name);
			*moving = true;
		}
		i++;
	}
	if (*moving)
		ft_printf("\n");
	else if (data->print_lines)
		ft_printf("END\n");
}

bool	print_result(t_data *data, t_input *input)
{
	int		nb_of_ants;
	bool	moving;
	int		line_number;

	if (data->number_of_paths == 0 || !save_paths(data))
		return (false);
	data->ants_on_path = (t_list **)malloc(sizeof(t_list *) * data->ants);
	if (!data->ants_on_path)
		return (false);
	print_elements(&(input->map));
	if (data->print_paths)
		print_paths(data);
	nb_of_ants = 0;
	moving = true;
	line_number = 1;
	while (moving)
	{
		add_ants_on_path(data, &nb_of_ants);
		print_moves(data, &nb_of_ants, &moving, &line_number);
	}
	return (true);
}
