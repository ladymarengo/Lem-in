/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:11:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/07/28 12:47:21 by jheiskan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <stdbool.h>

# define MAX_INT 2147483647

typedef struct s_array
{
	char	**array;
	size_t	size;
	size_t	nb_of_elements;
}	t_array;

typedef struct s_list
{
	int				room;
	struct s_list	*next;
}	t_list;

typedef struct s_room
{
	char	*name;
	bool	start;
	bool	end;
	t_list	*links;
	t_list	*input;
	t_list	*output;
	int		bfs_level;
}	t_room;

typedef struct s_room_array
{
	t_room	*rooms;
	size_t	size;
	size_t	nb_of_elements;
}	t_room_array;

typedef struct s_input_flags
{
	bool	parsing_links;
	bool	start;
	bool	end;
	bool	next_s;
	bool	next_e;
}	t_input_flags;

typedef struct s_input
{
	t_input_flags	flags;
	t_array			rooms;
	t_array			links;
	long int		ants;
	char			*line;
	char			*start;
	char			*end;
}	t_input;


typedef enum e_connection
{
	NO_CONNECTION,
	NO_FLOW,
	FLOW,
}	t_connection;

typedef struct s_bfs
{
	t_list			*queue;
	bool			*visited;
	int				*parents;
	int				current;
	t_connection	**new_conn;
	int				*tmp_capacity;
	int				*path_lengths;
	int				number_of_paths;
	t_list			*tmp;
	int				link;
}	t_bfs;

typedef enum e_return
{
	FAIL,
	NEW_PATH,
	NO_PATH,
}	t_return;

typedef struct s_path
{
	int		ants;
	int		length;
	t_list	*path;
}	t_path;

typedef struct s_data
{
	int				ants;
	int				number_of_rooms;
	t_room			*rooms;
	int				*capacity;
	int				moves;
	int				start;
	int				end;
	t_connection	**connections;
	t_bfs			bfs;
	t_list			*shortest_path;
	t_path			*paths;
	int				number_of_paths;
}	t_data;


void	print_connections(t_data *data);
bool	sort_array(char **arr, int size);
bool	del_structure_array(t_array *array);
void	del_array(char **array, size_t size);
bool	realloc_array(t_array *array);
bool	init_struct_array(t_array *new);
bool	add_element(t_array *array, char *element);
void	print_elements(t_array *array);
bool	check_ants(char *line, long int *ants);
bool	check_input(t_input *input, int fd);
bool	post_input_check(t_input *input);
bool	no_dups(t_array *rooms);
bool	handle_commands(t_input_flags *flags, char *line);
void	parse_start_end(t_input *input, t_data *data);
bool	make_rooms(t_input *input, t_data *data);
int		binary_search(char **array, char *str, int start, int end);
bool	parse_links(t_input *input, t_data *data);
bool	add_to_start(t_list **a, int index);
bool	add_to_end(t_list **a, int index);
bool	find_node(t_list *list, int number);
bool	print_list(t_list *list);
void	del_list(t_list *list);
void	del_room(t_room *room);
int		pop_first_node(t_list **a);
void	print_rooms_links(t_data *data);
void	del_elem(t_list **list, int elem);
void	print_paths(t_data *data);
int		count_turns(t_data *data);
bool	solve(t_data *data);
bool	print_result(t_data *data, t_input *input);

#endif