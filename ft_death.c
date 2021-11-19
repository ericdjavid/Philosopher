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

t_bool is_philo_dead(t_data *data, t_bool is_dead)
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

void *death_upcoming(void *phil)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)phil;
    i = 0;

    while (is_philo_dead(philo->data, FALSE) == FALSE)
    {
        ft_usleep(philo->data->ttd + 1);
        i++;
        pthread_mutex_lock(&philo->data->eat_mutex);
        if (philo->start_eating == FALSE)
        {
            print_action(philo, RED "died" END);
            // pthread_mutex_lock(&philo->data->print_action);
            // printf(RED "\n%ld Philo %d died\n" END, actual_time() - philo->initial_time - i, philo->id);
            is_philo_dead(philo->data, TRUE);
            pthread_mutex_unlock(&philo->data->print_action);
            pthread_mutex_unlock(&philo->data->eat_mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&philo->data->eat_mutex);
    }
    pthread_exit(NULL);

    // ft_usleep(philo->data->ttd + 1);
    // pthread_mutex_lock(&philo->data->eat_mutex);
    // if (philo->start_eating == FALSE)
    // {
    //     is_philo_dead(philo->data, TRUE);
    //     pthread_mutex_lock(&philo->data->print_action);
    //     printf(RED "\n%ld Philo %d died\n" END, actual_time() - philo->initial_time - 1, philo->id);
    //     pthread_mutex_unlock(&philo->data->print_action);
    //     pthread_mutex_unlock(&philo->data->eat_mutex);
    //     pthread_exit(NULL);
    // }
    // pthread_mutex_unlock(&philo->data->eat_mutex);
    // pthread_exit(NULL);
}
