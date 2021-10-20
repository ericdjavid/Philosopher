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

/* Prototypes:

                            ---THREADS---
int pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);
        --> pthread_create(&id[0], NULL, printNumber, &arg);
int pthread_cancel (pthread_t thread);  --> Annuler le thread
int pthread_join (pthread_t th, void ** thread_return);  --> Rejoindre le thread

                            ---TIME---
int gettimeofday(struct timeval *tv, struct timezone *tz); --> Lire/écrire l'heure actuelle  
int usleep(useconds_t usec);


                            ---MUTEX---
create mutex --> static pthread_mutex_t mutex_stock = PTHREAD_MUTEX_INITIALIZER;
lock mutex --> int pthread_mutex_lock (pthread_mutex_t * mutex);
unlcok mutex --> int pthread_mutex_unlock (pthread_mutex_t * mutex);

*/

#include "ft_philosopher.h"

int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (1);

    printf("\n argc is %d\n", argc);
    s_data *data;
    if (!init_data(data, argc, argv))
        return (1);

    //TODO #1 creat 1 thread per philosopher (argv1)
    pthread_t id[2];
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);

    usleep(100000);
    gettimeofday(&end, NULL);

    double tml1 = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
    double tml2 = (end.tv_sec) * 1000 + (end.tv_usec) / 1000;
    //tooktime /= 1000;
    printf("\nstarted at %f and ended at %f, it tooks %d millisecond\n", tml1, tml2, (int)(tml2 - tml1));
}