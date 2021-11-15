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

    time = actual_time() - philo->initial_time ;
    printf("\n%ld %d is %s\n", time, philo->id, action);
}

t_bool reach_die(t_philo *philo, long int actual)
{
    long int delay;
    
    delay = actual - philo->initial_time;
    printf(PINK"\nDelay is %ld\n"END, delay);
    if (delay >= philo->data->ttd)
    {
        print_action(philo, "died");
        return (TRUE);
    }
    return (FALSE);
}

int ft_eat(long int time, t_philo *philo)
{
    // if has no forks
        // try to get forks
    // if has 2 forks
   // pthread_mutex_lock(&philo->data->print_action);
    print_action(philo, "eating");
    ft_usleep(philo->data->tte);
    philo->eaten_time = actual_time();
    philo->has_eaten = TRUE;
    //pthread_mutex_unlock(&philo->data->print_action);
    return (SUCCESS);
}

int ft_sleep(long int time, t_philo *philo)
{
    //pthread_mutex_lock(&philo->data->print_action);
    print_action(philo, "sleeping");
    ft_usleep(philo->data->tts);
    philo->has_slept = TRUE;
   // pthread_mutex_unlock(&philo->data->print_action);
    return (SUCCESS);
}

void *death_upcoming(void *philo)
{
    t_philo *phil;

    phil = (t_philo *)philo;
    while (!(phil->data->is_philo_dead))
    {
        ft_usleep(5);
        long int tms = actual_time() - phil->initial_time; 
        printf(YELLOW"\ntms is %ld\n"END, tms);
        if (tms >= phil->data->ttd /* && is not finished ? */)
        {
            phil->data->is_philo_dead = TRUE;
            print_action(phil, "died");
            break ;
        }
    } 
    pthread_exit(NULL);
}

void *ft_live(void *philo)
{
    t_philo *clone;
    
    clone = (t_philo*)philo;
    clone->initial_time = actual_time();
    //while the philo is NOT dead
    while (!(clone->data->is_philo_dead))
    {
        //create death thread
        pthread_create(&clone->data->death, NULL, death_upcoming, (void *)philo);
        //eat
        if(!clone->has_eaten)
            ft_eat(actual_time() - clone->initial_time, clone);
        //sleep
        if((clone->has_eaten) && (!(clone->has_slept)))
            ft_sleep(actual_time() - clone->initial_time, clone);
        //think
    }
        //TODO: REINITIALISER LES VARS  
        pthread_exit(NULL);
}
