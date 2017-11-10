/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:21:59 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/10 18:57:16 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

// static void aff_lst(t_room *head)
// {
//     int poid;
//     t_room *tmp;
//     t_link *link;

// 	tmp = head;
// 	poid = 0;
//     while (tmp)
//     {
//         ft_putstr("name: ");
// 		ft_putstr(tmp->name);
// 		ft_putstr(" - role: ");
// 		ft_putnbr(tmp->role);
// 		ft_putstr(" - poid: ");
// 		ft_putnbr(tmp->poid);
// 		ft_putchar('\n');
// 		if (tmp->role > 0)
// 			poid++;
// 		link = tmp->link;
// 		if (link)
// 			ft_putstr("    tubes: ");
// 		while (link)
// 		{
// 			ft_putchar(' ');
// 			ft_putstr(link->ptr->name);
// 			if (link->next)
// 			{
// 				ft_putchar(' ');
// 				ft_putchar('-');
// 			}
//             link = link->next;
// 		}
// 		ft_putchar('\n');
//         tmp = tmp->next;
// 	}
// }

static void		init_data(t_data **data)
{
	(*data)->nb_f = -1;
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
	int 		fd;

	fd = -1;
	data = malloc(sizeof(t_data));
	init_data(&data);
	if (ac != 2)
		error_map();
	if ((fd = open_map(av[1])) == -1)
		return (-1);
	parse_map(fd, &data);
	check_map(data);
	if (get_path(data) == -1)
		error_map();
	// ft_putstr("FOURMI : ");
	// ft_putnbr(data->nb_f);
	// ft_putchar('\n');
	// ft_putendl("#############");
	// aff_lst(data->head);
	// ft_putendl("#############");

	ft_putchar('\n');
	make_anthill(data);
	go_fourmi(data);
	return (0);
}
