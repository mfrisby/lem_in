#include "../includes/lemin.h"

static int      ft_isnumber(char *s)
{
    while (*s)
    {
        if (!ft_isdigit(*s))
            return (-1);
        s++;
    }
    return (1);
}

static int    parse(t_env *e, char *s, int is_fourmi)
{
    t_node  *node;
    char **t;

    node = malloc(sizeof(t_node));
    node->content = NULL;
    node->left = NULL;
    node->right = NULL;
    if (is_fourmi == 0 && ft_isnumber(s))
    {
        e->fourmis = ft_atoi(s);
        return (1);
    }
    else if (s[0] != '#' && ft_strchr(s, '-') != NULL)
    {
        t = ft_strsplit(s, '-');
        ft_add_node(node, t[0], 0);
        ft_add_node(node, t[1], 1);
    }
    return (0);
}

static void    read_file(t_env *e, int fd)
{
    int is_fourmi;
    char *line;

    is_fourmi = 0;
    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        if (!line)
            break ;
        if (parse(e, line, is_fourmi) > 0)
            is_fourmi = 1;
        ft_putendl(line);
    }
}

int    open_file(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    return (fd);
}

int     main(int ac, char **av)
{
    t_env *e;
    int fd;

    e = malloc(sizeof(t_env));
    fd = 0;
    if (ac < 2)
    {
        ft_putendl("Please add a file.");
        return (-1);
    }
    fd = open_file(av[1]);
    read_file(e, fd);
    return (0);
}