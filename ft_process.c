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

t_bool reach_die(t_philo *philo, long int actual)
{
    long int delay;

    printf(PINK "\nDelay is %ld\n" END, delay);
    if (delay >= philo->data->ttd)
    {
        print_action(philo, "died");
        return (TRUE);
    }
    return (FALSE);
}

int ft_eat(t_philo *philo)
{
    // if has no forks
    // try to get forks
    // if has 2 forks
    // pthread_mutex_lock(&philo->data->eat_mutex);
    if (philo->has_eaten == TRUE)
    {
        // pthread_mutex_unlock(&philo->data->eat_mutex);
        return (FAILURE);
    }
    print_action(philo, YELLOW "is eating" END);
    ft_usleep(philo->data->tte);
    philo->eaten_time = actual_time();
    philo->has_eaten = TRUE;
    // pthread_mutex_unlock(&philo->data->eat_mutex);
    print_action(philo, YELLOW "finished eating" END);
    return (SUCCESS);
}

int ft_sleep(long int time, t_philo *philo)
{
    //pthread_mutex_lock(&philo->data->print_action);
    //pthread_mutex_lock(&philo->data->death);
    print_action(philo, "sleeping");
    // pthread_mutex_unlock(&philo->data->death);
    ft_usleep(philo->data->tts);
    philo->has_slept = TRUE;
    // pthread_mutex_unlock(&philo->data->print_action);
    return (SUCCESS);
}

void *death_upcoming(void *phil)
{
    t_philo *philo;

    philo = (t_philo *)phil;
    ft_usleep(philo->data->ttd + 1);
    if (is_philo_dead(philo->data, TRUE))
    {
        pthread_mutex_lock(&philo->data->print_action);
        printf(RED "\n%ld Philo %d died\n" END, actual_time() - philo->initial_time - 1, philo->id);
        pthread_mutex_unlock(&philo->data->print_action);
    }
    pthread_exit(NULL);
}

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

void *ft_live(void *philo)
{
    t_philo *clone;

    clone = (t_philo *)philo;
    clone->initial_time = actual_time();
    //create death thread
    pthread_create(&clone->data->death, NULL, death_upcoming, (void *)philo);
    // ft_usleep(1);
    while (is_philo_dead(clone->data, FALSE) == FALSE)
    {
        print_tms(clone);
        if (clone->has_eaten == FALSE)
        {
            print_action(clone, "started eating");
            ft_usleep(clone->data->tte);
            print_action(clone, "finished eating");
        }
    }
    printf("\nFinished execution\n");
    pthread_exit(NULL);
}
