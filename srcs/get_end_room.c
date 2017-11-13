/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:56:12 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/10 18:56:16 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room  *get_end_room(t_room *head)
{
	static t_room  *room = NULL;

	if (!room)
	{
		while (head)
		{
			if (head->role == E_ROOM)
			{
				room = head;
				break ;
			}
			head = head->next;
		}
	}
	return (room);
}
