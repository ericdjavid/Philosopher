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

void *affect_forks(void *ptr)
{
    printf("\nthread created for philo");
    pthread_exit(NULL);
}

//START BY 1 PHILO
int create_philo_threads(t_data *data, int philo_nb)
{
    int i;
    t_philo *philo;
    pthread_t pt1;

    philo = malloc(sizeof(*philo));
    philo->td = &pt1;
    philo->id = 1;
    philo->next = NULL;
    data->first = philo;
    pthread_create(&pt1, NULL, affect_forks, data);

    //    while (++i < philo_nb)
    //    {
    //        printf("\ncreating thread for philo %d", i);
    //        pthread_create(&id, NULL, print_created, "lolcat");
    //    }
    sleep(3);
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
    pthread_mutex_t mymutex;
    data->print_mutex = mymutex;
    printf("\n nb of philo : %d", data->nb_philo);
    printf("\n time to die : %d", data->ttd);
    printf("\n time to eat: %d", data->tte);
    printf("\n time to sleep: %d", data->tts);
    return (data);
}
