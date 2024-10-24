#include "cub3d.h"

int	err_msg(char *msg, int err)
{
    errno = err;
    ft_putendl_fd("Error", 2);
    ft_putendl_fd(msg, 2);
    ft_putstr_fd("Error code: ", 2);
    ft_putnbr_fd(errno, 2);
    ft_putstr_fd(" - ", 2);
    perror(NULL);
    return (err);
}

int handle_error(t_data *data, int err, char *msg)
{
    err_msg(msg, err);
    cub_free(data);
    exit(err);
}
