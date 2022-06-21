/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:53:04 by jheiskan          #+#    #+#             */
/*   Updated: 2022/06/21 15:27:37 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**copy_array(char **arr, int start, int size)
{
	int		i;
	char	**new;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (false);
	i = 0;
	while (i < size)
	{
		new[i] = arr[i + start];
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	final_merge(char **arr, char **first, char **second, int start)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (first[i1] && second[i2])
	{
		if (ft_strcmp(first[i1], second[i2]) < 0)
			arr[start] = first[i1++];
		else
			arr[start] = second[i2++];
		start++;
	}
	while (first[i1])
		arr[start++] = first[i1++];
	while (second[i2])
		arr[start++] = second[i2++];
}

bool	merge_arrays(char **arr, int start, int mid, int end)
{
	char	**first;
	char	**second;

	first = copy_array(arr, start, mid - start + 1);
	if (!first)
		return (false);
	second = copy_array(arr, mid + 1, end - mid);
	if (!second)
	{
		free(first);
		return (false);
	}
	final_merge(arr, first, second, start);
	free(first);
	free(second);
	return (true);
}

bool	merge_sort(char **arr, int start, int end)
{
	int	mid;

	if (start < end)
	{
		mid = (end - start) / 2 + start;
		if (!merge_sort(arr, start, mid) || !merge_sort(arr, mid + 1, end))
			return (false);
		if (!merge_arrays(arr, start, mid, end))
			return (false);
	}
	return (true);
}

bool	sort_array(char **arr, int size)
{
	if (!merge_sort(arr, 0, size - 1))
		return (false);
	return (true);
}
