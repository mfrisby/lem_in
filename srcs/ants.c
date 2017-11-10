/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:55:42 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/10 19:02:13 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static t_ant	*make_ant(int name, t_room *start)
{
	t_ant		*ant;

	ant = malloc(sizeof(t_ant) + 1);
	ant->name = ft_itoa(name);
	ant->next = NULL;
	ant->room = start;
	return (ant);
}

void			make_anthill(t_data *data)
{
	int			i;
	t_ant		*ant;
	t_ant		*tmp;

	i = 1;
	ant = NULL;
	tmp = NULL;
	while (i <= data->nb_f)
	{
		ant = make_ant(i, get_start_room(data->head));
		if (data->ants == NULL)
			data->ants = ant;
		else
		{
			tmp = data->ants;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = ant;
		}
		i++;
	}
}
