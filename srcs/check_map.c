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

static int  recursive(t_room *room, t_room *parent)
{
    t_room *tmp;

    if (!room || room == parent)
        return (-1);
    if (room->role == E_ROOM)
    {
        ft_putendl("SUCCESS");
        return (1);
    }
    while (room->link)
    {
        ft_putstr("\nrecursive: ");
        ft_putendl(room->name);
        if (room->link->ptr != parent)
        {
            tmp = room->link->ptr;
        }
        else if (room->link->next)
            tmp = room->link->next->ptr;
        else
            return (-1);
        return (recursive(tmp, room));
    }
    return (-1);
}

int         check_map(t_data *data)
{
    t_room  *start;

    start = get_start_room(data->head);
    check_start_end(start);
    if (data->nb_f <= 0)
        error_map();
    if (!start)
        return (-1);
    if (recursive(start, NULL) == 1)
        ft_putendl("\nSUCCESS");
    else
        ft_putendl("\nFAIL");
    return (0);
}