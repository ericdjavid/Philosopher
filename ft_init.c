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

int init_philo(t_data *data)
{
    t_philo *philo;

    philo = malloc(sizeof(*philo));
    if (!philo)
        return (FAILURE);
    philo->id = 1;
    philo->next = NULL;
    philo->start_eating = FALSE;
    philo->has_think = FALSE;
    philo->has_slept = FALSE;
    philo->eaten_time = 0;
    philo->data = data;
    philo->initial_time = 0;
    pthread_mutex_init(&philo->left_fork, NULL);
    philo->right_fork = NULL;
    data->first = philo;
    printf("\nSuccessfully created philo n.1\n");
    return (SUCCESS);
}

t_bool new_philo(t_philo *first, int nb)
{
    t_philo *philo;
    t_philo *tmp;

    philo = malloc(sizeof(*philo));
    if (!philo || !first)
        return (FAILURE);
    tmp = first;
    philo->id = nb;
    philo->start_eating = FALSE;
    philo->has_think = FALSE;
    philo->has_slept = FALSE;
    philo->data = first->data;
    philo->initial_time = 0;
    philo->eaten_time = 0;
    pthread_mutex_init(&philo->left_fork, NULL);
    philo->right_fork = NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = philo;
    philo->next = NULL;
    printf("\nSuccessfully created philo n. %d\n", nb);
    return (SUCCESS);
}

int add_philo_chain(int philo_nb, t_philo *first)
{
    t_philo *tmp;
    int i;

    i = 1;
    printf("\nphilo nb is %d\n", philo_nb);
    tmp = first;
    while (i++ < philo_nb)
        new_philo(first, i);
    while (tmp->next)
    {
        tmp->right_fork = &tmp->next->left_fork;
        tmp = tmp->next;
    }
    if (philo_nb > 1)
        tmp->right_fork = &first->left_fork;
    return (SUCCESS);
}

int create_philo_threads(t_data *data, int philo_nb)
{
    t_philo *first;
    t_philo *tmp;
    int ret;
    int i;

    ret = 0;
    i = 0;
    if (init_philo(data))
        return (FAILURE);

    first = data->first;
    add_philo_chain(data->nb_philo, first);
    //TODO: create thread for all

    tmp = first;
    // pthread_create(&data->first->td, NULL, ft_live, (void *)first);
    while (i < data->nb_philo)
    {
        ret = pthread_create(&tmp->td, NULL, ft_live, (void *)tmp);
        if (ret != 0)
        {
            printf("Error : issue while thread creation");
            return (FAILURE);
        }
        tmp = tmp->next;
        i++;
    }
    return (SUCCESS);
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
    pthread_mutex_init(&data->print_action, NULL);
    pthread_mutex_init(&data->death_mutex, NULL);
    pthread_mutex_init(&data->eat_mutex, NULL);
    printf("\n nb of philo : %d", data->nb_philo);
    printf("\n time to die : %d", data->ttd);
    printf("\n time to eat: %d", data->tte);
    printf("\n time to sleep: %d", data->tts);
    return (data);
}
