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

void* print_created(void *ptr)
{
    printf("\nthread successfully created with the pointer %p", &ptr);
    pthread_exit(NULL);
}

int init_thread(t_data *data, pthread_t id)
{
    // FIXME: USE MUTEX
    pthread_create(&id, NULL, print_created, "lolcat");
    //params : mutex id, NULL, function to call, pointer to use (can be NULL);
}

int create_philo_threads(t_data *data, int philo_nb)
{
    int i;
    pthread_t id[philo_nb - 1];
    t_philo *philo[philo_nb];
    
    //TODO: t_elem first = id[0]
    // then link them with liste chainees
    i = -1;
    while (++i < philo_nb)
    {
        printf("\ncreating thread for philo %d", i); 
        init_thread(data, id[i]);
    }
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
    data = malloc(sizeof(t_data));
    if (data == NULL)
        return (NULL);
    data->optionnal = FALSE;
    if (argc == 5)
        data->optionnal = TRUE;
    data->nb_philo = get_values(argv[1]);
    data->ttd = get_values(argv[2]);
    data->tte = get_values(argv[3]);
    data->tts = get_values(argv[4]);
    pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
    data->print_mutex = mymutex;
    printf("\n nb of philo : %d", data->nb_philo);
    printf("\n time to die : %d", data->ttd);
    printf("\n time to eat: %d", data->tte);
    printf("\n time to sleep: %d", data->tts);
    return (data);
}
