/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <e.djavid@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:20:13 by edjavid           #+#    #+#             */
/*   Updated: 2021/10/20 17:20:17 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

void *affect_forks(void *data)
{
    printf("\nthread created for philo");
}

//TODO: ADD PHILO FUNCTION WITH LISTE CHAINEES
int init_philo(t_data *data)
{
    t_philo *philo;

    philo = malloc(sizeof(*philo));
    if (!philo)
        return (FAILURE);
    philo->id = 1;
    philo->next = NULL;
    philo->has_eaten = FALSE;
    philo->has_think = FALSE;
    philo->has_slept = FALSE;
    philo->data = data;
    philo->initial_time = 0;
    philo->right_fork = NULL;
    data->first = philo;
    return (SUCCESS);
}

t_philo *new_philo(t_data *data, int nb)
{
    t_philo *philo;

    philo = malloc(sizeof(*philo));
    if (!philo)
        return (NULL);
    philo->id = nb;
    philo->next = NULL;
    philo->has_eaten = FALSE;
    philo->has_think = FALSE;
    philo->has_slept = FALSE;
    philo->data = data;
    philo->initial_time = 0;
    philo->right_fork = NULL;
    printf("\nSuccessfully created philo n. %d\n", nb);
    return (new_philo);
}

int add_philo_chain(int philo_nb, t_philo *first)
{
    t_philo *tmp;
    int     i;

    tmp = first;
    i = 1;
    printf("\nphilo nb is %d\n", philo_nb);
    while (i < philo_nb)
    {
        //TODO: PROBLEM
        tmp->next = new_philo(first->data, ++i);
        if (!tmp->next)
            return (FAILURE);
        tmp = tmp->next;
    }
    return (SUCCESS); 
}

int create_philo_threads(t_data *data, int philo_nb)
{
    t_philo *first;
    if (init_philo(data))
        return (FAILURE);    
    
    first = data->first;
    add_philo_chain(data->nb_philo, first);
    ft_usleep(10000);
    pthread_create(&data->first->td, NULL, ft_live, (void*)first);

    return (1);
}

int get_values(char *str)
{
    int i;
    int size;
    int nb;

    i = 0;
    nb = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (FAILURE);
        nb *= 10;
        nb = nb + ((str[i] - '0'));
        i++;
    }
    return (nb);
}

t_data *init_data(int argc, char **argv)
{
    t_data *data;
    pthread_mutex_t mymutex;

    data = malloc(sizeof(*data));
    if (data == NULL)
        return (NULL);
    data->optionnal = FALSE;
    if (argc == 5)
        data->optionnal = TRUE;
    data->nb_philo = get_values(argv[1]);
    data->ttd = get_values(argv[2]);
    data->tte = get_values(argv[3]);
    data->tts = get_values(argv[4]);
    data->is_philo_dead = FALSE;
    data->print_action = mymutex;
    data->initial_time = (long int)actual_time();
    printf("\n nb of philo : %d", data->nb_philo);
    printf("\n time to die : %d", data->ttd);
    printf("\n time to eat: %d", data->tte);
    printf("\n time to sleep: %d", data->tts);
    return (data);
}
