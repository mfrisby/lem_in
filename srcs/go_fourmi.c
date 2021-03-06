/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_fourmi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:57:04 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/13 10:23:04 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static void		make_step(t_ant *ant, t_link *link)
{
	ant->room->fourmi--;
	ant->room = link->ptr;
	ant->room->fourmi++;
	ft_putchar('L');
	ft_putstr(ant->name);
	ft_putchar('-');
	ft_putstr(ant->room->name);
	ft_putchar(' ');
}

static void		recursive_step(t_ant *head)
{
	t_ant		*ant;
	t_link		*link;

	ant = head;
	link = ant->room->link;
	while (link)
	{
		if (ant->room->role == E_ROOM)
			break ;
		if ((link->ptr->role == PATH && link->ptr->fourmi == 0
			&& link->ptr->poid < ant->room->poid)
			|| link->ptr->role == E_ROOM)
		{
			make_step(ant, link);
			break ;
		}
		link = link->next;
	}
	if (ant->next)
		recursive_step(ant->next);
}

void			go_fourmi(t_data *data)
{
	t_room		*start;
	t_room		*end;

	start = get_start_room(data->head);
	start->fourmi = data->nb_f;
	end = get_end_room(data->head);
	while (end->fourmi < data->nb_f)
	{
		recursive_step(data->ants);
		ft_putchar('\n');
	}
}
