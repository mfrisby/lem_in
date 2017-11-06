/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:20:43 by mfrisby           #+#    #+#             */
/*   Updated: 2017/05/02 16:21:44 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>

# define				EMPTY		0
# define				FULL		1
# define				ROOM		0
# define				S_ROOM		1
# define				E_ROOM		2
# define				DEAD_END	-1
# define				PATH		5

typedef	struct			s_link {
	char				*name;
	struct s_room		*ptr;
	struct s_link		*next;
}						t_link;

typedef struct			s_room {
	int					condition;
	int					role;
	char				*name;
	struct s_link		*link;
	struct s_room		*next;
}						t_room;

typedef struct			s_data {
	int					nb_f;//fourmi total
	struct s_room		*head;
	struct s_room		*tail;
}						t_data;

void        parse_map(int fd, t_data **data);
void    	error_map();
int         check_map(t_data *data);
t_room		*get_start_room(t_room *head);
t_room		*get_end_room(t_room *head);
t_room      *get_room_by_name(char *name, t_room *head);

#endif
