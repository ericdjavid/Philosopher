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

char *str = "lolcat";

void* print_created(void *ptr)
{
    printf("\nthread successfully created with the pointer %p", &ptr);
    pthread_exit(NULL);
}

int init_thread(pthread_t id)
{
    pthread_create(&id, NULL, print_created, &str);
    //params : if, NULL, function to call, pointer to use (can be NULL);
}

int create_philo_threads(int philo_nb)
{
    int i;
    pthread_t id[philo_nb - 1]; 
    
    i = -1;
    while (++i < philo_nb)
    {
        printf("\ncreating thread for philo %d", i);   
        init_thread(id[i]);
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
        return (FAILURE);
    data->optionnal = FALSE;
    if (argc == 5)
        data->optionnal = TRUE;
    data->nb_philo = get_values(argv[1]);
    data->ttd = get_values(argv[2]);
    data->tte = get_values(argv[3]);
    data->tts = get_values(argv[4]);
    printf("\n nb of philo : %d", data->nb_philo);
    printf("\n time to die : %d", data->ttd);
    printf("\n time to eat: %d", data->tte);
    printf("\n time to sleep: %d", data->tts);
    return (data);
}
