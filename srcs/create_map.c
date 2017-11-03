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

static int  get_start_end(char *buf, int *is_start, int *is_end)
{
    if (ft_strcmp("##start", buf) == 0 && *is_start == 0)
        *is_start = 1;
    else if (ft_strcmp("##start", buf) == 0 && *is_start == 1)
        return (-1);
    else if (ft_strcmp("##end", buf) == 0 && *is_end == 0)
        *is_end = 1;
    else if (ft_strcmp("##end", buf) == 0 && *is_end == 1)
        return (-1);
    return (0);
}

static void get_room(char *buf, int is_start, int is_end, t_data **data)
{
    t_room  *room;
    char    **split;

    room = NULL;
    (void)is_start;
    (void)is_end;
    (void)data;
    buf = ft_splitblank(buf)[0];
    split = ft_strsplit(buf, '-');
    ft_putendl(buf);
    room = malloc(sizeof(t_room) + 1);
}

void        create_map(int fd, t_data **data)
{
    int     is_start;
    int     is_end;
    char    *buf;

    buf = NULL;
    is_start = 0;
    is_end = 0;
    while (get_next_line(fd, &buf))
    {
        if (!buf || ft_strlen(buf) <= 0)
		    break ;
        get_fourmi(buf, data);
        if (get_start_end(buf, &is_start, &is_end) == -1)
            break ;
        get_room(buf, is_start, is_end, data);
    }
}


// static void		parse_map(int fd, t_data **data)
// {
// 	char *buf;
// 	char **split;

// 	split = NULL;
// 	buf = NULL;
// 	while (get_next_line(fd, &buf))
// 	{
// 		
// 		split = ft_splitblank(buf);
// 		if (!split || !split[0] || ft_strlen(split[0]) <= 0)
// 			break ; 
// 		if (ft_strcmp(split[0], "##start") == 0)
// 			ft_putendl(buf);
// 		else if (ft_strcmp(split[0], "##end") == 0)
// 			ft_putendl(buf);
// 		else
// 		{
// 			split = ft_strsplit(buf, '-');
// 			if (ft_isnumber(split[0]) != 0 && ft_isnumber(split[1]) != 0)
// 				ft_putendl(buf);
// 		}
// 	}
// }