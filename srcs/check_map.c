/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:55:52 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/11 18:54:07 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static void		check_start_end(t_room *start)
{
	int			startok;
	int			endok;

	startok = 0;
	endok = 0;
	while (start)
	{
		if (start->role == E_ROOM)
			endok = 1;
		else if (start->role == S_ROOM)
			startok = 1;
		if (startok == 1 && endok == 1)
			return ;
		start = start->next;
	}
	if (endok == 0 || startok == 0)
		error_map();
}

void			check_map(t_data *data)
{
	t_room		*start;

	if (!data->head)
		error_map();
	start = get_start_room(data->head);
	check_start_end(start);
	if (data->nb_f <= 0)
		error_map();
}
