/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 22:18:46 by sgardner          #+#    #+#             */
/*   Updated: 2018/02/03 00:54:00 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "wolf3d.h"

void		fatal_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

static int	count_args(char *arg)
{
	int	count;

	count = 0;
	while (*arg)
	{
		if (*arg != ' ' && (*(arg + 1) == ' ' || *(arg + 1) == '\0'))
			count++;
		arg++;
	}
	return (count);
}

char		**split(char *arg)
{
	char	**arr;
	int		size;
	int		i;

	size = count_args(arg);
	if (!(arr = ft_memalloc(sizeof(char *) * (size + 1))))
		DEFAULT_ERROR;
	i = 0;
	while (*arg)
	{
		while (*arg == ' ')
			*arg++ = '\0';
		if (*arg)
			arr[i++] = arg;
		while (*arg && *arg != ' ')
			arg++;
	}
	return (arr);
}
