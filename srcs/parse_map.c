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

static void get_room(char *buf, int role, t_data **data)
{
    t_room  *room;

    if (!buf)
        return ;
    room = malloc(sizeof(t_room) + 1);
    room->condition = EMPTY;
    room->role = role;
    room->name = buf;
    room->link = NULL;
    room->next = NULL;
    if (!(*data)->head)
        (*data)->head = room;
    if ((*data)->tail)
        (*data)->tail->next = room;
    (*data)->tail = room;
}

static void add_link(char *buf, t_room *head)
{
    t_link  *link;
    char    **split;

    link = NULL;
    split = ft_strsplit(buf, '-');
    if (!split || !split[0] || !split[1])
        return ;
    while (head)
    {
        if (ft_strcmp(head->name, split[0]) == 0)
        {
            if (!head->link)
            {
                head->link = malloc(sizeof(t_link) + 1);
                head->link->next = NULL;
                head->link->name = ft_strdup(split[1]);
                return ;
            }
            link = head->link;
            while (link->next)
                link = link->next;
            link->next = malloc(sizeof(t_link) + 1);
            link->next->name = ft_strdup(split[1]);
            link->next->next = NULL;
            return ;
        }
        head = head->next;
    }
}

static void aff_lst(t_room *head)
{
    while (head)
    {
        ft_putstr("\nname: ");
        ft_putstr(head->name);
        while (head->link)
        {
            ft_putstr("  link: ");
            ft_putstr(head->link->name);
            head->link = head->link->next;
        }
        head = head->next;
    }
}

static int  get_special_room(char *buf)
{
    if (ft_strcmp("##start", buf) == 0)
        return (S_ROOM);
    else if (ft_strcmp("##end", buf) == 0)
        return (E_ROOM);
    return (ROOM);
}

void        parse_map(int fd, t_data **data)
{
    int     role;
    char    *buf;

    buf = NULL;
    role = ROOM;
    while (get_next_line(fd, &buf))
    {
        if (!buf || ft_strlen(buf) <= 0)
            break ;
        if ((*data)->nb_f != -1 && ft_isnumber(buf) != 0)
            error_map();
        if (get_fourmi(buf, data) == -1)
            continue ;
        if ((role = get_special_room(buf) != 0))
            continue ;
        if (ft_strchr(buf, '-') != NULL)
        {
            add_link(buf, (*data)->head);
            continue ;
        }
        else
            get_room(ft_splitblank(buf)[0], role, data);
        role = ROOM;
    }
    aff_lst((*data)->head);
}