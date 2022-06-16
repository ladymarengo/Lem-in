/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheiskan <jheiskan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:11:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/06/16 12:16:25 by jheiskan         ###   ########.fr       */
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
	char			*line;
	bool			start;
	bool			end;
	struct s_list	*next;
}	t_list;

typedef struct s_rooms_links
{
	struct s_list	*rooms;
	struct s_list	*links;
	int				rooms_len;
}	t_rooms_links;

typedef struct s_input_flags
{
	bool	parsing_links;
	bool	start;
	bool	end;
	bool	next_start;
	bool	next_end;
}	t_input_flags;

bool	del_structure_array(t_array *array);
void	del_array(char **array, size_t size);
bool	realloc_array(t_array *array);
t_array	*init_struct_array(void);
bool	add_element(t_array *array, char *element);
void	print_elements(t_array *array);


#endif