/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:07:24 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/03 01:35:51 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		FATAL_ERROR("usage: wolf3d <map-filename>\n");
	map = load_map(av[1]);
	return (0);
}
