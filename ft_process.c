/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:19:37 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/12 18:19:39 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

int print_action(t_philo *philo, char *action)
{
    long int time;

    pthread_mutex_lock(&philo->data->death_mutex);
    if (philo->data->is_philo_dead == TRUE)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->death_mutex);
    time = actual_time() - philo->initial_time;
    pthread_mutex_lock(&philo->data->print_action);
    printf("\n%ld Philo %d %s\n", time, philo->id, action);
    pthread_mutex_unlock(&philo->data->print_action);
    return (SUCCESS);
}


//TODO: OPTION FACULTATIVE
void *ft_live(void *philo)
{
    t_philo *clone;
    int i = 0;
    long int timer;

    clone = (t_philo *)philo;
    clone->initial_time = actual_time();
    //create death thread
    // pthread_create(&clone->data->death, NULL, death_upcoming, (void *)philo);
    pthread_create(&clone->death, NULL, death_upcoming, (void *)clone);
    // printf(BLUE"process philo %d initiated\n"END, clone->id);
    while (is_philo_dead(clone->data, FALSE) == FALSE)
    {
        pthread_mutex_lock(&clone->data->eat_mutex);
        if (clone->start_eating == FALSE)
        {
            // TODO: FORK PROCESS
            pthread_mutex_lock(&clone->left_fork);
            print_action(clone, "has taken a fork");
            pthread_mutex_lock(clone->right_fork);
            print_action(clone, "has taken a fork");
            clone->start_eating = TRUE;
            clone->eaten_time = actual_time();
            pthread_mutex_unlock(&clone->data->eat_mutex);
            print_action(clone, "started eating");
            ft_usleep(clone->data->tte);
            pthread_mutex_unlock(clone->right_fork);
            pthread_mutex_unlock(&clone->left_fork);
            // print_action(clone, "finished eating");
        }
        pthread_mutex_unlock(&clone->data->eat_mutex);
        // pthread_mutex_lock(&clone->data->sleep_think_mutex);
        if (clone->has_slept == FALSE)
        {
            print_action(clone, "started sleeping");
            ft_usleep(clone->data->tts);
            print_action(clone, "started thinking");
            // pthread_mutex_unlock(&clone->data->sleep_think_mutex);
            // print_action(clone, "finished sleeping");
            // clone->eaten_time = actual_time();
        }
        // pthread_mutex_unlock(&clone->data->sleep_think_mutex);
        pthread_mutex_lock(&clone->data->eat_mutex);
        if (clone->start_eating && clone->has_slept)
        {
            clone->start_eating = FALSE;
            pthread_mutex_unlock(&clone->data->eat_mutex);
            // TODO : PBM with start thinking
            // print_action(clone, "started thinking");
        // pthread_mutex_lock(&clone->data->sleep_think_mutex);
            clone->has_slept = FALSE;
        // pthread_mutex_unlock(&clone->data->sleep_think_mutex);
        }
        pthread_mutex_unlock(&clone->data->eat_mutex);
    }
    // printf("\nFinished loop %d", clone->id);
    pthread_exit(NULL);
}
