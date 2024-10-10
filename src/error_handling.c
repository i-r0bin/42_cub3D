#include "cub3d.h"

int	err_msg(char *msg, int err)
{
    errno = err;
    perror(msg);
    return (err);
}
