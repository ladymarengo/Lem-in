/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:10:01 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/21 17:16:54 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	binary_search(char **array, char *str, int start, int end)
{
	int	mid;
	int	compare_result;

	mid = start + (end - start) / 2;
	compare_result = ft_strcmp(str, array[mid]);
	if (start == end && compare_result != 0)
		return (-1);
	if (compare_result == 0)
		return (mid);
	else if (compare_result < 0)
		return (binary_search(array, str, start, mid));
	else
		return (binary_search(array, str, mid + 1, end));
}