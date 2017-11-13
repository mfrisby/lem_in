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

// static void		aff_lst(t_room *head)
// {
// 	t_room		*tmp;
// 	t_link		*link;

// 	tmp = head;
// 	while (tmp)
// 	{
// 		ft_printf("name: %s - role: %d - poid: %d\n"
// 				, tmp->name, tmp->role, tmp->poid);
// 		link = tmp->link;
// 		if (link)
// 			ft_putstr("    tubes: ");
// 		while (link)
// 		{
// 			ft_putchar(' ');
// 			ft_putstr(link->ptr->name);
// 			if (link->next)
// 				ft_putstr(" -");
// 			link = link->next;
// 		}
// 		ft_putchar('\n');
// 		tmp = tmp->next;
// 	}
// }

static void		init_data(t_data **data)
{
	(*data)->nb_f = -1;
	(*data)->has_end = 0;
	(*data)->head = NULL;
	(*data)->tail = NULL;
	(*data)->ants = NULL;
}

int				main(void)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	init_data(&data);
	parse_map(0, &data);
	check_map(data);
	if (get_path(data) == -1)
		error_map();
	make_anthill(data);
	go_fourmi(data);
	return (0);
}
