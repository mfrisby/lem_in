
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

// static void     get_error(t_room *room)
// {
//     int     check;
//     t_link *tmp;

//     if (room->role == E_ROOM)
//         return;
//     check = 0;
//     tmp = room->link;
//     while (tmp)
//     {
//         if ((tmp->ptr->role == PATH || tmp->ptr->role == E_ROOM) && tmp->ptr->poid < room->poid)
//         {
//             check = 1;
//         }
//         tmp = tmp->next;
//     }
//     if (check == 0)
//     {
//         room->role = ROOM;
//         ft_putstr(room->name);
//         ft_putendl(" ERROR");
//     }
// }

static void  recursive_step(t_ant *head)
{
    t_ant   *ant;
    t_link  *link;

    ant = head;
    link = ant->room->link;
    while (link)
    {
        //get_error(ant->room);
        if (ant->room->role == E_ROOM)
            break;
        // else if ((link->ptr->role == PATH && link->ptr->fourmi == 1) || link->ptr->poid > ant->room->poid)
        // {
        //     link = link->next;
        //     continue;
        // }
        else if (((link->ptr->role == PATH && link->ptr->fourmi == 0) 
                    || link->ptr->role == E_ROOM) && link->ptr->poid < ant->room->poid)
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
        if (round > 500)//secure DEBUG
            break;
        recursive_step(data->ants);
        //TODO
        //AJOUT CHOIX SALLE POID LE PLUS FAIBLE 
        ft_putchar('\n');
        round++;
    }
    ft_putstr("round: ");
    ft_putnbr(round);
    ft_putstr(" fourmis: ");
    ft_putnbr(end->fourmi);
    ft_putstr(":\n");
}