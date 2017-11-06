#include "../includes/lem-in.h"

t_room  *get_end_room(t_room *head)
{
    static t_room  *room = NULL;

    if (!room)
    {
        while (head)
        {
            if (head->role == E_ROOM)
            {
                room = head;
                break ;
            }
            head = head->next;
        }
    }
    return (room);
}