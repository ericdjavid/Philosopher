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

int print_action(int id, long int tms, char *action)
{
    //TODO: write & ATOI
    printf("\n%ld %d is %s\n", tms, id, action);
}

t_bool reach_die(t_philo *philo, long int actual)
{
    long int delay;
    
    delay = actual - philo->initial_time;
    //printf("\nDelay is %ld\n", delay);
    if (delay > philo->data->ttd)
        return (TRUE);
    return (FALSE);
}

int ft_eat(long int time, t_philo *philo)
{
    // if has no forks
        // try to get forks
    // if has 2 forks
    print_action(philo->id, time, "eating");
    philo->has_eaten = TRUE;
    return (SUCCESS);
}

void* ft_live(void *philo)
{
    t_philo *clone;
    
    clone = (t_philo*)philo;

    //du coup plutot mettre le initial time ds chque philo
    clone->initial_time = actual_time();
    //while no philo is dead
    while (!(clone->data->is_philo_dead))
    {
        if(!clone->has_eaten)
            ft_eat((actual_time() - clone->initial_time), clone);
        if(reach_die(clone, actual_time()))
            clone->data->is_philo_dead = TRUE;
    //take 2 forks
    //eat
    //sleep
    //think

    }
    printf("a philo is dead\n");
    
    
}
