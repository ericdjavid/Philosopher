#include "ft_philosopher.h"

void free_elems(t_philo *first)
{
    t_philo *tmp;

    tmp = first;
    while(tmp)
    {
        first = first->next;
        free(tmp);
        tmp = first;
    }
}

int ft_free_all(t_data *data)
{
    if (data->first)
        free_elems(data->first);
    if (data)
        free(data);
    return (SUCCESS);
}