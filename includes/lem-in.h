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

# define				EMPTY	0
# define				FULL	1
# define				ROOM	0
# define				S_ROOM	1
# define				E_ROOM	2

typedef struct			s_room {
	int					condition;
	int					role;
	char				*name;
	struct s_room		*left;
	struct s_room		*right;
}						t_room;

typedef struct			s_data {
	int					nb_f;//fourmi total
	int					nb_fs;//fourmi in start room
	int					nb_fe;//fourni in end room
	struct s_room		*head;
}						t_data;

void        create_map(int fd, t_data **data);

#endif
