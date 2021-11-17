/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:29:21 by edjavid           #+#    #+#             */
/*   Updated: 2021/10/19 15:29:23 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ------RULES------ */
// 1+ philo around the table
// they can eat, think, sleep
// they can only do 1 thing at time
// they need 2 forks to eat spaghetti
// when philo finished eating, he drops the forks and starts sleeping
// when philo finished sleeping, he will start thinking (meaning just wait for eat, no tms in params)
// if time to die is spent and philo didn't eat, he dies
// when a philo dies, simulation stops

// ARGUMENTS (all the times are in ms):
//  ./philosopher [nb_pilo_&_forks(1 to n)] [time_to_die] [time_to_eat] [time_to_sleep] [nb_eat_before_end (optionnal)]

/* 
STDIN messages :
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died

other:
- one fork between each philosopher
- each philosopher is a thread
- protect fork state with a mutex for each of the;
*/
#include "ft_philosopher.h"

int main(int argc, char **argv)
{
    t_data *data;
    void *ret;

    if (argc != 5 && argc != 6)
        return (1);
    data = init_data(argc, argv);

    if (create_philo_threads(data, data->nb_philo) == FAILURE)
        return 2;

    //TODO: wait for end of threads before the end of main
    //(void)pthread_join(data->first->td,&ret);

    (void)pthread_join(data->first->td, &ret);
    (void)pthread_join(data->death, &ret);

    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_destroy(&data->eat_mutex);
    pthread_mutex_destroy(&data->print_action);
    ft_free_all(data);
    //TODO: do fourchette process

    return 0;
}