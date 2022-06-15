/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:42:39 by jheiskan          #+#    #+#             */
/*   Updated: 2022/06/15 15:22:29 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_elements(t_array *array)
{
	int	i;

	i = 0;
	ft_printf("Number of elements: %u\nSize of array: %u\n", array->nb_of_elements, array->size);
	while(i < array->nb_of_elements)
		ft_printf("%s\n", array->array[i++]);
	ft_putchar('\n');
}

t_array *init_struct_array(void)
{
	t_array	*new;

	new = (t_array *)malloc(sizeof(t_array));
	if (!new)
		return (NULL);
	new->nb_of_elements = 0;
	new->size = 2;
	new->array = (char **)malloc(sizeof(char *) * new->size);
	if (!new->array)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

bool	add_element(t_array *array, char *element)
{
	if (array->nb_of_elements >= array->size && !realloc_array(array))
		return (false);
	array->array[array->nb_of_elements] = ft_strdup(element);
	if (!array->array[array->nb_of_elements])
		return (false);
	array->nb_of_elements++;
	return (true);
}

bool	del_structure_array(t_array *array)
{
	if (!array)
		return (true);
	while (array->nb_of_elements-- > 0)
		if (array->array[array->nb_of_elements])
			free(array->array[array->nb_of_elements]);
	free(array->array);
	free(array);
	return (true);
}

void	del_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

bool	realloc_array(t_array *array)
{
	char	**new;
	int		i;

	i = 0;
	array->size *= 2;
	new = (char **)malloc(sizeof(char *) * array->size);
	if (!new && del_structure_array(array))
		return (false);
	ft_bzero(new, sizeof(new));
	while (array->nb_of_elements > i)
	{
		new[i] = ft_strdup(array->array[i]);
		if (!new[i] && del_structure_array(array))
		{
			del_array(new, array->nb_of_elements);
			return (false);
		}
		i++;
	}
	del_array(array->array, array->nb_of_elements);
	array->array = new;
	return (true);
}