/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:21:59 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/13 10:52:40 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static void		aff_lst(t_room *head)
{
	t_room		*tmp;
	t_link		*link;

	tmp = head;
	while (tmp)
	{
		ft_printf("name: %s - role: %d - poid: %d\n"
				, tmp->name, tmp->role, tmp->poid);
		link = tmp->link;
		if (link)
			ft_putstr("    tubes: ");
		while (link)
		{
			ft_putchar(' ');
			ft_putstr(link->ptr->name);
			if (link->next)
				ft_putstr(" -");
			link = link->next;
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

static void		init_data(t_data **data)
{
	(*data)->nb_f = -1;
	(*data)->has_end = 0;
	(*data)->head = NULL;
	(*data)->tail = NULL;
	(*data)->ants = NULL;
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
	int			fd;

	fd = -1;
	data = malloc(sizeof(t_data));
	init_data(&data);
	if (ac == 3 && (ft_strcmp(av[2], "--debug") != 0))
		error_map();
	if (ac != 2)
		error_map();
	if ((fd = open_map(av[1])) == -1)
		return (-1);
	parse_map(fd, &data);
	check_map(data);
	if (get_path(data) == -1)
		error_map();
	if (ac == 3)
	{
		aff_lst(get_start_room(data->head));
		ft_putchar('\n');
	}
	make_anthill(data);
	go_fourmi(data);
	return (0);
}
