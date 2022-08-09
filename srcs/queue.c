/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:03:38 by jheiskan          #+#    #+#             */
/*   Updated: 2022/08/09 12:03:39 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs_path	*new_node_path(t_list *path, int index)
{
	t_bfs_path	*new;
	t_list		*list;

	new = (t_bfs_path *)malloc(sizeof(t_bfs_path));
	if (!new)
		return (NULL);
	new->path = NULL;
	list = path;
	add_to_start(&(new->path), index);
	while (list)
	{
		add_to_end(&(new->path), list->room);
		list = list->next;
	}
	new->next = NULL;
	return (new);
}

bool	add_to_end_path(t_bfs_path **a, t_list *path, int index)
{
	t_bfs_path	*tmp;
	t_bfs_path	*list;

	if (!a)
		return (false);
	if (!*a)
	{
		(*a) = new_node_path(path, index);
		if (!(*a))
			return (false);
	}
	else
	{
		list = *a;
		while (list->next)
			list = list->next;
		tmp = new_node_path(path, index);
		if (!tmp)
			return (false);
		list->next = tmp;
	}
	return (true);
}

t_list	*pop_first_node_path(t_bfs_path **a)
{
	t_list		*path;
	t_bfs_path	*tmp;

	path = (*a)->path;
	tmp = (*a)->next;
	free(*a);
	*a = tmp;
	return (path);
}
