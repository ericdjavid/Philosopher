#include "ft_philosopher.h"

int ft_free_all(t_data *data)
{
    if (data->first)
    {
// while ... free all philos
        free(data->first);
    }
    if (data)
        free(data);
    return (SUCCESS);
}