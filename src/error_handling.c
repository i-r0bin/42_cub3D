#include "cub3d.h"

int	err_msg(char *msg, int err, int ret)
{
    ft_putstr_fd(msg, 1);
    if (err == ERR_USAGE)
        ft_putendl_fd(": Usage: ./cub3D map.cub", 1);
    else if (err == ERR_FILE)
        ft_putendl_fd(": Could not open file", 1);
    else if (err == ERR_RES)
        ft_putendl_fd(": Invalid resolution", 1);
    else if (err == ERR_TEX)
        ft_putendl_fd(": Invalid texture", 1);
    else if (err == ERR_COLOR)
        ft_putendl_fd(": Invalid color", 1);
    else if (err == ERR_MAP)
        ft_putendl_fd(": Invalid map", 1);
    return (ret);
}
