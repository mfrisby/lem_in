#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static void check_start_end(t_room *start)
{
    int startok;
    int endok;

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

static t_room  *check_end(t_link *link)
{
    while (link)
    {
        if (link->ptr->role == E_ROOM)
            return (link->ptr);
        link = link->next;
    }
    return (NULL);
}

static int      recursive(t_room *room, t_room *parent)
{
    int         ret;
    t_room      *tmp;
    t_link      *link;

    if (!room || room == parent)
        return (-1);
    room->visited = VISITED;
    if (room->role == E_ROOM)
        return (1);
    link = room->link;
    while (link)
    {
        ret = 0;
        tmp = check_end(link);
        if (!tmp && link->ptr != parent && link->ptr->visited == NOT_VISITED)
            tmp = link->ptr;
        else if (!tmp && !link->next)
            return (-1);
        if (tmp)
        {
            ret = recursive(tmp, room);
            if (ret > 0)
            {
                ret++;
                room->poid = ret;
                if (room->role == ROOM)
                    room->role = PATH;
                return (ret);
            }
        }
        link = link->next;
    }
    return (ret);
}

int         check_map(t_data *data)
{
    t_room  *start;
    int i;

    i = 0;
    start = get_start_room(data->head);
    check_start_end(start);
    if (data->nb_f <= 0)
        error_map();
    if (!start)
        return (-1);
    //TODO
    // changer le multi path
    //il cree des chemins faux
    //toujours partir de start pour trouver chemin
    while (i < 10)
    {
        recursive(start, NULL);
        i++;
    }
    return (0);
}