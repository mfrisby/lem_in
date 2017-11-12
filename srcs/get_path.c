/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:56:22 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/10 18:56:25 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static t_room		*check_end(t_link *link, int poid, t_data *data)
{
	while (link)
	{
		if (link->ptr->role == S_ROOM)
		{
			link->ptr->poid = poid + 1;
			ft_putendl("ici");
			data->has_end = 1;
			return (link->ptr);
		}
		link = link->next;
	}
	return (NULL);
}

static int		check_room_role(t_room *room, int check)
{
	if (check == 1)
		if (room->role != S_ROOM && room->role != E_ROOM)
			room->role = PATH;
	return (check);
}

static int		recursive(t_room *room, t_room *parent, int poid, t_data *data)
{
	int		check;
	t_link		*link;

	check = 0;
	link = room->link;
	room->visited = VISITED;
	if (check_end(link, poid, data))
	{
		room->poid = poid;
		if (room->role == ROOM)
			room->role = PATH;
		return (1);
	}
	while (link)
	{
		if (link->ptr != parent && link->ptr->visited != VISITED
				&& recursive(link->ptr, room, poid + 1, data) > 0)
		{
			room->poid = poid;
			check = 1;
		}
		link = link->next;
	}
	return (check_room_role(room, check));
}

int			get_path(t_data *data)
{    
	int		ret;

	ret = recursive(get_end_room(data->head), NULL, 0, data);
	if (data->has_end != 1)
		error_map();
	return (ret);
}
