/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <e.djavid@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:06:58 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/19 19:07:00 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

t_bool  is_philo_dead(t_data *data, t_bool is_dead)
{
    pthread_mutex_lock(&data->death_mutex);
    if (is_dead == TRUE)
        data->is_philo_dead = TRUE;
    if (data->is_philo_dead == TRUE)
    {
        pthread_mutex_unlock(&data->death_mutex);
        return (TRUE);
    }
    pthread_mutex_unlock(&data->death_mutex);
    return (FALSE);
}
/* is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting his last meal or the beginning of the simulation, it
dies */
// if current time - time eat > time to die
void *death_upcoming(void *phil)
{
    t_philo *philo;

    philo = (t_philo *)phil;

    while (is_philo_dead(philo->data, FALSE) == FALSE)
    {
        ft_usleep(philo->data->ttd);

        // pthread_mutex_lock(&philo->data->sleep_think_mutex);
        if (philo->data->optionnal == TRUE && philo->nb_eat == philo->data->cycle)
        {
            // pthread_mutex_unlock(&philo->data->sleep_think_mutex);
            pthread_exit(NULL);
        }

        pthread_mutex_lock(&philo->data->eat_mutex);
        long int delta_eaten_time = actual_time() - philo->eaten_time;
        // printf(YELLOW"Philo %d, delta (actual time - beg eat time) is %ld\n"END, philo->id, delta_eaten_time);
        // if (philo->start_eating == FALSE)
        pthread_mutex_lock(&philo->data->sleep_think_mutex);
        if ((delta_eaten_time) >= philo->data->ttd && philo->start_eating == FALSE)
        {
            pthread_mutex_unlock(&philo->data->sleep_think_mutex);
            pthread_mutex_unlock(&philo->data->eat_mutex);
            print_action(philo, RED "died" END);
            // pthread_mutex_lock(&philo->data->print_action);
            // printf(RED "\n%ld Philo %d died\n" END, actual_time() - philo->initial_time - i, philo->id);
            is_philo_dead(philo->data, TRUE);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&philo->data->eat_mutex);
            pthread_mutex_unlock(&philo->data->sleep_think_mutex);
    }
    pthread_exit(NULL);
}
