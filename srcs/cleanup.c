/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:07:49 by jheiskan          #+#    #+#             */
/*   Updated: 2022/08/04 13:11:09 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	delete_connections(t_connection **connection, int len)
{
	int	i;

	i = 0;
	if (!connection)
		return ;
	while (i < len && connection[i])
		free(connection[i++]);
	free(connection);
}

void	cleanup_input(t_input *input)
{
	del_structure_array(&(input->rooms));
	del_structure_array(&(input->links));
	del_structure_array(&(input->map));
	if (input->line)
		free(input->line);
	if (input->start)
		free(input->start);
	if (input->end)
		free(input->end);
	if (input->fd != 0)
		close(input->fd);
}

void	cleanup_data(t_data *data)
{
	free(data->capacity);
	free(data->bfs.tmp_capacity);
	free(data->bfs.path_lengths);
	del_list(data->bfs.tmp);
	del_list(data->shortest_path);
	del_list(data->bfs.queue);
	if (data->paths)
	{
		while (data->number_of_paths-- > 0
			&& data->paths[data->number_of_paths].path)
			del_list(data->paths[data->number_of_paths].path);
		free(data->paths);
	}
	if (data->bfs.visited)
		free(data->bfs.visited);
	if (data->bfs.parents)
		free(data->bfs.parents);
	if (data->ants_on_path)
		free(data->ants_on_path);
	delete_connections(data->connections, data->number_of_rooms);
	delete_connections(data->bfs.new_conn, data->number_of_rooms);
	while (data->number_of_rooms-- > 0)
		del_room(&data->rooms[data->number_of_rooms]);
	free(data->rooms);
}

void	cleanup_and_exit(t_input *input, t_data *data, int ret, char *message)
{
	if (message)
		ft_printf("%s", message);
	cleanup_data(data);
	cleanup_input(input);
	exit(ret);
}
