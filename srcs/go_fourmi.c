
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static void ant_step_output(t_ant *ant)
{
    ft_putchar('L');
    ft_putstr(ant->name);
    ft_putchar('-');
    ft_putstr(ant->room->name);
    ft_putchar(' ');
}

static t_link   *get_short_pass(t_link *link)
{
    int         poid;
    t_link      *tmp;
    t_link      *ret;

    poid = -1;
    tmp = link;
    ret = NULL;
    while (tmp)
    {
        if (tmp->ptr->role == PATH && tmp->ptr->fourmi == 0)
        {
            if (poid == -1)
            {
                poid = tmp->ptr->poid;
                ret = tmp;
            }
            if (tmp->ptr->poid < poid)
            {
                poid = tmp->ptr->poid;
                ret = tmp;
            }
        }
        tmp = tmp->next;
    }
    return (ret);
}

static void     make_step(t_ant *ant, t_link *link)
{
    ant->room->fourmi--;
    ant->room = link->ptr;
    ant->room->fourmi++;
    ant_step_output(ant);
}

static void     recursive_step(t_ant *head)
{
    t_ant   *ant;
    t_link  *link;
    t_link  *tmp;

    ant = head;
    link = ant->room->link;
    tmp = NULL;
    while (link)
    {
        if (ant->room->role == E_ROOM)
            break;
        tmp = get_short_pass(link);
        if (tmp)
            link = tmp;
        if ((link->ptr->role == PATH && link->ptr->fourmi == 0
                && link->ptr->poid < ant->room->poid) || link->ptr->role == E_ROOM)
        {
            make_step(ant, link);
            break;
        }
        link = link->next;
    }
    if (ant->next)
        recursive_step(ant->next);
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
        if (round > 500)
            break;
        recursive_step(data->ants);
        ft_putchar('\n');
        round++;
    }
    ft_putstr("round: ");
    ft_putnbr(round);
    ft_putchar('\n');
}