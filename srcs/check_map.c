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
    int ret;
    t_room *tmp;

    if (!room || room == parent)
        return (-1);
    ft_putstr(room->name);
    ft_putstr(" - ");        
    if (room->role == E_ROOM)
        return (1);
    while (room->link)
    {
        room->visited = VISITED;
        ret = 0;
        tmp = check_end(room->link);
        if (!tmp && room->link->ptr != parent && room->link->ptr->visited == NOT_VISITED)
            tmp = room->link->ptr;
        else if (!tmp && !room->link->next)
            return (-1);
        if (tmp)
        {
            ret = recursive(tmp, room);
            if (ret > 0)
            {
                if (room->role == ROOM)
                    room->role = PATH;
                return (1);
            }
        }
        room->link = room->link->next;
    }
    return (-1);
}

// static int  recursive(t_room *room, t_room *parent)
// {
//     int ret;
//     t_room *tmp;

//     ret = 0;
//     ft_putstr("\nrecursive: ");
//     ft_putendl(room->name);
//     if (!room || room == parent)
//         return (-1);
//     if (room->role == E_ROOM)
//         return (1);
//     while (room->link)
//     {
//         if (check_end(room->link) == 1)
//         {
//             if (room->role == ROOM)
//                 room->role = PATH;
//             return (1);
//         }
//         if (room->link->ptr == parent && !room->link->next)
//             return (-1);
//         if (room->link->ptr != parent)
//             tmp = room->link->ptr;
//         else
//             return (-1);
//         ret = recursive(tmp, room);
//         if (ret > 0)
//         {
//             if (room->role == ROOM)
//                 room->role = PATH;
//             return (ret);
//         }
//         ft_putchar('X');
//         room->link = room->link->next;
//     }
//     return (-1);
// }

int         check_map(t_data *data)
{
    t_room  *start;

    start = get_start_room(data->head);
    check_start_end(start);//verifie ##end ##start exist
    if (data->nb_f <= 0)
        error_map();//verifie les fourmi
    if (!start)
        return (-1);
    if (recursive(start, NULL) > 0)
        ft_putendl("\nSUCCESS");
    else
        ft_putendl("\nFAIL");
    return (0);
}