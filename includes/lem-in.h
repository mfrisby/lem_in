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

# define				VISITED		1
# define				NOT_VISITED	-1
# define				ROOM		0
# define				S_ROOM		1
# define				E_ROOM		2
# define				PATH		5

typedef	struct			s_link {
	char				*name;
	struct s_room		*ptr;
	struct s_link		*next;
}						t_link;

typedef struct			s_room {
	int					poid;//nbr de salle avant END -1 si DEAD END
	int					visited;// VISITED/NOT VISITED
	int					fourmi;
	int					role;//START END NORMAL
	char				*name;
	struct s_link		*link;
	struct s_room		*next;
}						t_room;

typedef	struct			s_ant {
	struct s_room		*room;
	char				*name;
	struct s_ant		*next;
}						t_ant;

typedef struct			s_data {
	int					nb_f;//fourmi total
	struct s_ant		*ants;
	struct s_room		*head;
	struct s_room		*tail;//TODO REMOVE MAYBE
}						t_data;

void        parse_map(int fd, t_data **data);
void    	error_map();
int         check_map(t_data *data);
void        go_fourmi(t_data *data);
t_room		*get_start_room(t_room *head);
t_room		*get_end_room(t_room *head);
t_room      *get_room_by_name(char *name, t_room *head);
void        make_anthill(t_data *data);

#endif
