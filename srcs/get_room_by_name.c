/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room_by_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:56:34 by mfrisby           #+#    #+#             */
/*   Updated: 2017/11/10 18:56:43 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

t_room          *get_room_by_name(char *name, t_room *head)
{
    while (head)
    {
        if (ft_strcmp(name, head->name) == 0)
            return (head);
        head = head->next;
    }
    return (NULL);
}
