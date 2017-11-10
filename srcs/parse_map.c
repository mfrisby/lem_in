#include <fcntl.h>
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static int get_fourmi(char *buf, t_data **data)
{
    if ((*data)->nb_f != -1)//Si doublon => break
     	return (-1);
    if (ft_isnumber(buf) != 0)//Si ligne inconnu => break
        (*data)->nb_f = ft_atoi(buf);
    return (1);
}

static int get_room(char *buf, int role, t_data **data)
{
    t_room  *room;

    if (!buf)
        return (-1);
    if (buf[0] == '#' || buf[0] == 'L')
        return (-1);
    room = malloc(sizeof(t_room) + 1);
    room->poid = 0;
    room->visited = NOT_VISITED;
    room->fourmi = 0;
    room->role = role;
    if (buf[0] == 'L')
        error_map();
    room->name = buf;
    room->link = NULL;
    room->next = NULL;
    if (!(*data)->head)
        (*data)->head = room;
    if ((*data)->tail)
        (*data)->tail->next = room;
    (*data)->tail = room;
    return (0);
}

static void add_link(char *rname, char *lname, t_room *head)
{
    t_link  *tmp;
    t_room  *r;
    t_room  *l;

    r = get_room_by_name(rname, head);
    l = get_room_by_name(lname, head);
    if (!r || !l)//si salle inconnu OSEF
        return ;
    if (!r->link)
    {
        r->link = malloc(sizeof(t_link) + 1);
        r->link->next = NULL;
        r->link->ptr = l;
        return ;
    }
    tmp = r->link;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(t_link) + 1);
    tmp->next->next = NULL;
    tmp->next->ptr = l;
}

static int        parse_buf(char *buf, t_data **data, int *role)
{
    char    **split;

    split = ft_splitblank(buf);
    if ((ft_strchr(split[0], '-') != NULL) && !split[1] //tube sont seuls sur une ligne
        && (*data)->head && (*data)->nb_f != -1)//tubes viennent apres salles et fourmis
    {
        if (*role > 0)//si start/end devant tubes
            return (-1);
        split = ft_strsplit(buf, '-');
        if (!split || !split[0] || !split[1])
            return (-1);
        add_link(split[0], split[1], (*data)->head);
        add_link(split[1], split[0], (*data)->head);
    }
    else if (split[0] && !split[1])//FOURMI
    {
        if (*role > 0)//si start/end devant fourmis
            return (-1);
        return get_fourmi(buf, data);
    }
    else if (split[0] && split[1] && split[2] //coordonnees existes
                && (ft_isnumber(split[1]) == 1) && (ft_isnumber(split[2]) == 1))//coordonnees nombres entiers
        return (get_room(split[0], *role, data));
    return (0);
}

void        parse_map(int fd, t_data **data)
{
    char    *buf;
    int     role;

    buf = NULL;
    role = ROOM;
    while (get_next_line(fd, &buf))
    {
        ft_putendl(buf);
        if (!buf || ft_strlen(buf) <= 0)//ligne vide || EOF => ERROR
            break ;
        if (ft_strcmp("##start", buf) == 0)
        {
            role = S_ROOM;
            continue ;
        }
        else if (ft_strcmp("##end", buf) == 0)
        {
            role = E_ROOM;
            continue ;
        }
        else if (ft_splitblank(buf)[0][0] == '#')//ignore commentaires et cmd inconnues
            continue;
        if (parse_buf(buf, data, &role) == -1)
            break ;
        role = ROOM;
    }
}