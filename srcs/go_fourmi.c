
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static int  recursive_step(t_ant *head)
{
    t_ant   *ant;
    t_link  *link;

    ant = head;
    link = ant->room->link;
    while (link)
    {
        if (ant->room->role == E_ROOM)
            break;
        else if ((link->ptr->role == PATH && link->ptr->fourmi == 1) || link->ptr->path < ant->room->path)
        {
            link = link->next;
            continue;
        }
        else if (link->ptr->role == PATH || link->ptr->role == E_ROOM)
        {
            ant->room->fourmi--;
            ant->room = link->ptr;
            ant->room->fourmi++;
            ft_putchar('L');
            ft_putstr(ant->name);
            ft_putchar('-');
            ft_putstr(ant->room->name);
            ft_putchar(' ');
            break;
        }
        link = link->next;
    }
    if (ant->next)
        recursive_step(ant->next);
    return (0);
}

void        go_fourmi(t_data *data)
{
    int     round;
    t_room  *start;
    t_room  *end;

    round = 0;
    start = get_start_room(data->head);
    start->fourmi = data->nb_f;
    end = get_end_room(data->head);
    while (end->fourmi < data->nb_f)
    {
        if (round > 50)
            break;
        recursive_step(data->ants);
        ft_putchar('\n');
        round++;
    }
}