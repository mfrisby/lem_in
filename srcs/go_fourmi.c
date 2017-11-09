
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static void ant_step_output(t_ant *ant)
{
    ft_putchar('L');
    ft_putstr(ant->name);
    ft_putchar('-');
    ft_putstr(ant->room->name);
    ft_putchar(':');
    ft_putnbr(ant->room->poid);
    ft_putchar(' ');
}

static void  recursive_step(t_ant *head)
{
    t_ant   *ant;
    t_link  *link;

    ant = head;
    link = ant->room->link;
    while (link)
    {
        if (ant->room->role == E_ROOM)
            break;
        else if ((link->ptr->role == PATH && link->ptr->fourmi == 1) || link->ptr->poid > ant->room->poid)
        {
            link = link->next;
            continue;
        }
        else if (link->ptr->role == PATH || link->ptr->role == E_ROOM)
        {
            ant->room->fourmi--;
            ant->room = link->ptr;
            ant->room->fourmi++;
            ant_step_output(ant);
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
        if (round > 100)//secure DEBUG
            break;
        recursive_step(data->ants);
        //TODO
        //AJOUT CHOIX SALLE POID LE PLUS FAIBLE 
       // ft_putchar('\n');
        round++;
    }
    ft_putchar(':');
    ft_putnbr(end->fourmi);
    ft_putstr(":\n");
}