#include <fcntl.h>
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static int get_fourmi(char *buf, t_data **data)
{
    char    **split;

    split = NULL;
    if ((*data)->nb_f != -1)
     	return (1);
    split = ft_splitblank(buf);
    if (split[0] && !split[1] && ft_isnumber(split[0]) != 0)
        (*data)->nb_f = ft_atoi(split[0]);
    return (-1);
}

static void get_room(char *buf, int *role, t_data **data)
{
    t_room  *room;

    if (!buf)
        return ;
    room = malloc(sizeof(t_room) + 1);
    room->poid = 0;
    room->visited = NOT_VISITED;
    room->fourmi = 0;
    room->role = *role;
    room->name = buf;
    room->link = NULL;
    room->next = NULL;
    if (!(*data)->head)
        (*data)->head = room;
    if ((*data)->tail)
        (*data)->tail->next = room;
    (*data)->tail = room;
    *role = 0;
}

static void add_link(char *rname, char *lname, t_room *head)
{
    t_link  *tmp;
    t_room  *r;
    t_room  *l;

    r = get_room_by_name(rname, head);
    l = get_room_by_name(lname, head);
    if (!r || !l)
        error_map();
    if (!r->link)
    {
        r->link = malloc(sizeof(t_link) + 1);
        r->link->next = NULL;
        r->link->name = ft_strdup(lname);//TODO REMOVE link->name UNUSED
        r->link->ptr = l;
        return ;
    }
    tmp = r->link;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(t_link) + 1);
    tmp->next->next = NULL;
    tmp->next->name = ft_strdup(lname);
    tmp->next->ptr = l;
}

void        parse_map(int fd, t_data **data)
{
    int     role;
    char    *buf;
    char    **split;

    buf = NULL;
    split = NULL;
    role = ROOM;
    while (get_next_line(fd, &buf))
    {
        if (!buf || ft_strlen(buf) <= 0)
            break ;
        if ((*data)->nb_f != -1 && ft_isnumber(buf) != 0)
            error_map();
        if (get_fourmi(buf, data) == -1)
            continue ;
        if (ft_strcmp("##start", buf) == 0)
        {
            role = S_ROOM;
            continue ;
        }
        if (ft_strcmp("##end", buf) == 0)
        {
            role = E_ROOM;
            continue ;
        }
        if (buf[0] == '#' || buf[0] == 'L')
            continue;
        if (ft_strchr(buf, '-') != NULL)
        {
            split = ft_strsplit(buf, '-');
            if (!split || !split[0] || !split[1])
                break ;
            add_link(split[0], split[1], (*data)->head);
            add_link(split[1], split[0], (*data)->head);
        }
        else
            get_room(ft_splitblank(buf)[0], &role, data);
    }
}