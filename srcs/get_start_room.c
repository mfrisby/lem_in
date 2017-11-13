/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_room.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:56:53 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/10 18:56:58 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room  *get_start_room(t_room *head)
{
	static t_room  *room = NULL;

	if (!room)
	{
		while (head)
		{
			if (head->role == S_ROOM)
			{
				room = head;
				break;
			}
			head = head->next;
		}
	}
	return (room);
}
