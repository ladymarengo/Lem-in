/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:11:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/21 12:11:20 by jheiskan         ###   ########.fr       */
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

// typedef struct s_list
// {
// 	char			*line;
// 	bool			start;
// 	bool			end;
// 	struct s_list	*next;
// }	t_list;

// typedef struct s_rooms_links
// {
// 	struct s_list	*rooms;
// 	struct s_list	*links;
// 	int				rooms_len;
// }	t_rooms_links;

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
	struct s_input_flags	flags;
	struct s_array			rooms;
	struct s_array			links;
	long int				ants;
	char					*line;
}	t_input;

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

#endif