/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:24:39 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/21 12:52:39 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <inttypes.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_tags
{
	int		hash;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		width;
	int		precision;
	char	*length;
	char	specifier;
}	t_tags;

int		ft_printf(const char *format, ...);
void	free_tags(t_tags *tags);
void	parse_flags(char **format, t_tags *tags);
void	parse_width(char **format, t_tags *tags);
void	parse_precision(char **format, t_tags *tags);
void	parse_length(char **format, t_tags *tags);
void	print_specifier(char **format, t_tags *tags, va_list args, int *chars);
void	print_left_or_right(char **str, t_tags *tags, int *chars);
void	print_c(t_tags *tags, va_list args, int *chars);
void	print_s(t_tags *tags, va_list args, int *chars);
void	print_di(t_tags *tags, va_list args, int *chars);
void	print_poux(t_tags *tags, va_list args, int *chars);
void	print_f(t_tags *tags, va_list args, int *chars);
void	subtract_format(t_tags *tags, int *add, char *str);
void	add_format(t_tags *tags, char **str, int *chars);
int		num_with_prec(t_tags *tags);
int		is_sign(t_tags *tags, char c);
void	error_exit(t_tags *tags, int strs, ...);

#endif