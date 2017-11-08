#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

void        make_anthill(t_data *data)
{
    int     i;
    t_ant   *ant;
    t_ant   *tmp;
    t_room  *start;

    i = 1;
    ant = NULL;
    tmp = NULL;
    start = get_start_room(data->head);
    while (i <= data->nb_f)
    {
        ant = malloc(sizeof(t_ant) + 1);
        ant->name = ft_itoa(i);
        ant->next = NULL;
        if (!start)
            ft_putendl("start no set");
        ant->room = start;
        if (data->ants == NULL)
            data->ants = ant;
        else
        {
            tmp = data->ants;
            while (tmp && tmp->next)
                tmp = tmp->next;
            tmp->next = ant;
        }
        i++;
    }
}