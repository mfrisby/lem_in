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

int         check_map(t_data *data)
{
    t_room  *start;
    int i;

    i = 0;
    if (!data->head)
        error_map();
    start = get_start_room(data->head);
    check_start_end(start);
    if (data->nb_f <= 0)
        error_map();
    return (0);
}