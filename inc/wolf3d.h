/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 19:44:47 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/03 03:08:54 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <errno.h>
# include <string.h>
# include "libft.h"

# include <stdio.h> // REMOVE BEFORE SUBMISSION

# define FATAL_ERROR(msg) fatal_error(msg)
# define DEFAULT_ERROR FATAL_ERROR(strerror(errno))
# define MAP_ERROR FATAL_ERROR("Map error\n")

typedef struct	s_map
{
	int			**arr;
	int			*raw;
	int			x_max;
	int			y_max;
}				t_map;

/*
** load.c
*/

t_map			*load_map(char *path);

/*
** util.c
*/

void			fatal_error(char *msg);
char			**split(char *arg);
#endif
