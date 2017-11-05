/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:21:59 by mfrisby           #+#    #+#             */
/*   Updated: 2017/05/02 17:30:24 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static void		init_data(t_data **data)
{
	(*data)->nb_f = -1;
	(*data)->head = NULL;
	(*data)->tail = NULL;
}

static int		open_map(char *file)
{
	int			fd;
	
	fd = open(file, O_RDONLY);
	return (fd);
}

int				main(int ac, char **av)
{
	t_data		*data;
	int 		fd;

	fd = -1;
	data = malloc(sizeof(t_data));
	init_data(&data);
	if (ac != 2)
		ft_putendl("You MUST set ONE file.");
	if ((fd = open_map(av[1])) == -1)
		return (-1);
	parse_map(fd, &data);
	//check_map() check if start & end & nb fourmi & chemin possible
	return (0);
}