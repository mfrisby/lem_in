#include "../includes/lem-in.h"

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



int     get_path(t_data *data)
{    
    t_room  *start;
    int i;

    i = 0;
    start = get_start_room(data->head);
    while (i < 10)
    {
        recursive(start, NULL);
        i++;
    }
    return (0);
}