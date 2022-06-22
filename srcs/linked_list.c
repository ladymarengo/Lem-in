/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:43 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/22 15:07:00 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	find_node(t_list *list, int number)
{
	t_list	*tmp;

	while (list)
	{
		if (list->room == number)
			return (true);
		tmp = list->next;
		list = tmp;
	}
	return (false);
}

void	del_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

t_list	*new_node(int index)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->room = index;
	new->next = NULL;
	return (new);
}

bool	add_to_start(t_list **a, int index)
{
	t_list	*tmp;

	if (!a || !*a)
		(*a) = new_node(index);
	else
	{
		tmp = new_node(index);
		tmp->next = *a;
		*a = tmp;
	}
	if (!(*a))
		return (false);
	return (true);
}

bool	add_to_end(t_list **a, int index)
{
	t_list	*tmp;

	if (!a)
		return (false);
	if (!*a)
		(*a) = new_node(index);
	else
	{
		while ((*a)->next)
			*a = (*a)->next;
		tmp = new_node(index);
		if (!tmp)
			return (false);
		(*a)->next = tmp;
	}
	// all malloc protection
	return (true);
}

int	pop_first_node(t_list **a)
{
	int		number;
	t_list	*tmp;

	number = (*a)->room;
	tmp = (*a)->next;
	free(*a);
	*a = tmp;
	return (number);
}
