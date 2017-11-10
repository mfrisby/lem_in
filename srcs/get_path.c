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

static int          check_room_role(t_room *room, int check)
{
    if (check == 1)
        if (room->role != S_ROOM && room->role != E_ROOM)
            room->role = PATH;
    return (check);
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
        if (link->ptr != parent && link->ptr->visited != VISITED
                && recursive(link->ptr, room, poid + 1) > 0)
        {
            room->poid = poid;
            check = 1;
        }
        link = link->next;
    }
    return (check_room_role(room, check));
}

int     get_path(t_data *data)
{    
    int ret;

    ret = recursive(get_end_room(data->head), NULL, 0);
    if (ret == -1)
        error_map();
    return (ret);
}