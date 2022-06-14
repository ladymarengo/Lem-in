/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:43 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/14 15:41:27 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_stack(t_list *stack)
{
	t_list	*next;

	while (stack != NULL)
	{
		next = stack->next;
		ft_strdel(&(stack->line));
		free(stack);
		stack = next;
	}
}

t_list	*new_node(char *line, bool start, bool end)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->line = ft_strdup(line);
	new->start = start;
	new->end = end;
	return (new);
}

void	add_to_start(t_list **a, char *line, bool start, bool end)
{
	t_list	*tmp;

	if (!a || !*a)
		(*a) = new_node(line, start, end);
	else
	{
		tmp = new_node(line, start, end);
		tmp->next = *a;
		*a = tmp;
	}
}
