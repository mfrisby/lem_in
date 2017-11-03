#include <fcntl.h>
#include "../includes/lem-in.h"
#include "../libft/includes/libft.h"

static void get_fourmi(char *buf, t_data **data)
{
    char    **split;

    split = NULL;
    if ((*data)->nb_f != -1)
     	return ;
    split = ft_splitblank(buf);
    if (split[0] && !split[1] && ft_isnumber(split[0]) != 0)
        (*data)->nb_f = ft_atoi(split[0]);
}

static void get_room(char *buf, int *ret, t_data **data)
{
    t_room  *room;
    char    **split;

    room = NULL;
    (void)data;
    buf = ft_splitblank(buf)[0];
    split = ft_strsplit(buf, '-');
    if (*ret == 1)
        ft_putstr("\033[32m");
    else if (*ret == 2)
        ft_putstr("\033[31m");
    ft_putstr(split[0]);
    if (split[1])
    {
        ft_putstr(" - ");
        ft_putendl(split[1]);
    }
    else
        ft_putchar('\n');
    room = malloc(sizeof(t_room) + 1);
    ft_putstr("\033[0m");
    *ret = 0;
}

void        create_map(int fd, t_data **data)
{
    int ret;
    char    *buf;

    buf = NULL;
    ret = 0;
    while (get_next_line(fd, &buf))
    {
        if (!buf || ft_strlen(buf) <= 0)
		    break ;
        get_fourmi(buf, data);
        if (ft_strcmp("##start", buf) == 0)
        {
            ret = 1;
            continue;
        }
        else if (ft_strcmp("##end", buf) == 0)
        {
            ret = 2;
            continue;
        }
        get_room(buf, &ret, data);
    }
}