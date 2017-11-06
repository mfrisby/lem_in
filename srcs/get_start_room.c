#include "../includes/lem-in.h"

t_room  *get_start_room(t_room *head)
{
    static t_room  *room = NULL;

    if (!room)
    {
        while (head)
        {
            if (head->role == S_ROOM)
            {
                room = head;
                break;
            }
            head = head->next;
        }
    }
    return (room);
}