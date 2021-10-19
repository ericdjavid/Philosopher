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
// they canonly do 1 think at time
// they need 2 forks to eat spaghetti
// when philo finished eating, he drops the forks and start sleeping
// when philo finished sleeping, he will start thinking
// when a philo dies, simulation stops

/* ARGUMENTS :
//  ./philosopher [nb_pilo_&_forks(1 to n)] [time_to_die] [time_to_eat] [time_to_sleep] [nb_eat_before_end (optionnal)]

/* STDIN messages :
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
*/

/* other:
- one fork between each philosopher
- each philosopher is a thread
- protect fork state with a mutex for each of the;
*/
#include "ft_philosopher.h"

int main(int argc, char **argv)
{
    if (argc != 5 || argc != 6)
        return (1);

    //TODO #1 creat 1 thread per philosopher (argv1)
    pthread_t id[2]; 

    //pthread_create(&id[0], NULL, printNumber, &arg);

}