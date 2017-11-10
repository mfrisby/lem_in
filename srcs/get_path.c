#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"
#include  <stdio.h>

static t_room  *check_end(t_link *link, int poid)
{
    while (link)
    {
        if (link->ptr->role == S_ROOM)
        {
            link->ptr->poid = poid + 1;
            return (link->ptr);
        }
        link = link->next;
    }
    return (NULL);
}

static int          recursive(t_room *room, t_room *parent, int poid)
{
    int             check;
    t_link          *link;

    check = 0;
    link = room->link;
    room->visited = VISITED;
    if (check_end(link, poid))
    {
        room->poid = poid;
        room->role = PATH;
        return (1);
    }
    while (link)
    {
        if (link->ptr == parent || link->ptr->visited == VISITED)
        {
            link = link->next;
            continue;
        }
        if (recursive(link->ptr, room, poid + 1) > 0)
        {
            room->poid = poid;
            check = 1;
        }
        link = link->next;
    }
    if (check == 1)
    {
        if (room->role != S_ROOM && room->role != E_ROOM)
            room->role = PATH;
        return (1);
    }
    return (-1);
}

// static int      recursive(t_room *room, t_room *parent)
// {
//     int         ret;
//     t_room      *tmp;
//     t_link      *link;

//     if (!room || room == parent)
//         return (-1);
//     room->visited = VISITED;
//     if (room->role == E_ROOM)
//         return (1);
//     link = room->link;
//     while (link)
//     {
//         ret = 0;
//         //tmp = get_best_link(room, parent, 0);
//         if (!tmp && link->ptr != parent && link->ptr->visited == NOT_VISITED)
//             tmp = link->ptr;
//         if (!tmp && !link->next)
//             return (-1);
//         if (tmp)
//         {
//             ret = recursive(tmp, room);
//             if (ret > 0)
//             {
//                 ret++;
//                 room->poid = ret;
//                 if (room->role == ROOM)
//                     room->role = PATH;
//                 return (ret);
//             }
//         }
//         link = link->next;
//     }
//     return (ret);
// }



int     get_path(t_data *data)
{    
    int check;//si recursive renvoie 1 au moins une fois, il y a un chemin valide
    int ret;

    check = 0;
    ret = recursive(get_end_room(data->head), NULL, 0);
    if (ret == -1)
        ft_putendl("get path");
    return (ret);
}