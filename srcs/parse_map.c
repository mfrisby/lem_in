/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:57:20 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/13 14:40:00 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static int		get_fourmi(char *buf, t_data **data)
{
	if ((*data)->nb_f != -1)
		return (-1);
	if (ft_isnumber(buf) != 0)
		(*data)->nb_f = ft_atoi(buf);
	return (1);
}

static int		get_room(char *buf, int role, t_data **data)
{
	t_room		*room;

	if (!buf)
		return (-1);
	if (buf[0] == '#' || buf[0] == 'L')
		return (-1);
	room = malloc(sizeof(t_room) + 1);
	room->poid = 0;
	room->visited = NOT_VISITED;
	room->fourmi = 0;
	room->role = role;
	if (buf[0] == 'L')
		error_map();
	room->name = buf;
	room->link = NULL;
	room->next = NULL;
	if (!(*data)->head)
		(*data)->head = room;
	if ((*data)->tail)
		(*data)->tail->next = room;
	(*data)->tail = room;
	return (0);
}

static int		add_link(char *rname, char *lname, t_room *head)
{
	t_link		*tmp;
	t_room		*r;
	t_room		*l;

	r = get_room_by_name(rname, head);
	l = get_room_by_name(lname, head);
	if (!r || !l)
		return (-1);
	if (!r->link)
	{
		r->link = malloc(sizeof(t_link) + 1);
		r->link->next = NULL;
		r->link->ptr = l;
		return (0);
	}
	tmp = r->link;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_link) + 1);
	tmp->next->next = NULL;
	tmp->next->ptr = l;
	return (0);
}

static int		parse_buf(char **s, char *buf, t_data **data, int *role)
{
	if ((ft_strchr(s[0], '-') != NULL) && !s[1]
			&& (*data)->head && (*data)->nb_f != -1)
	{
		s = ft_strsplit(buf, '-');
		if (*role > 0 || !s || !s[0] || !s[1])
			return (-1);
		if ((add_link(s[0], s[1], (*data)->head)) == -1
			|| (add_link(s[1], s[0], (*data)->head) == -1))
			return (-1);
	}
	else if (s[0] && !s[1])
	{
		if (*role > 0)
			return (-1);
		return (get_fourmi(buf, data));
	}
	else if (s[0] && s[1] && s[2] && (ft_strchr(s[0], '-') != NULL))
		return (-1);
	else if (s[0] && (ft_strchr(s[0], '-') == NULL)
			&& s[1] && s[2]
			&& (ft_isnumber(s[1]) == 1) && (ft_isnumber(s[2]) == 1))
		return (get_room(s[0], *role, data));
	return (0);
}

void			parse_map(int fd, t_data **data, char *buf)
{
	int			role;

	buf = NULL;
	role = ROOM;
	while (get_next_line(fd, &buf))
	{
		if (!buf || ft_strlen(buf) <= 0)
			break ;
		ft_putendl(buf);
		if (ft_strcmp("##start", buf) == 0)
		{
			role = S_ROOM;
			continue ;
		}
		else if (ft_strcmp("##end", buf) == 0)
		{
			role = E_ROOM;
			continue ;
		}
		else if (ft_splitblank(buf)[0][0] == '#')
			continue;
		if (parse_buf(ft_splitblank(buf), buf, data, &role) == -1)
			break ;
		role = ROOM;
	}
}
