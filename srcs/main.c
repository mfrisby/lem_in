#include "../includes/lemin.h"

void    read_file(int fd)
{
    char *line;

    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        if (!line)
            break ;
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
    int fd;

    fd = 0;
    if (ac < 2)
    {
        ft_putendl("Please add a file.");
        return (-1);
    }
    fd = open_file(av[1]);
    read_file(fd);
    return (0);
}