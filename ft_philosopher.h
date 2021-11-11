/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:29:57 by edjavid           #+#    #+#             */
/*   Updated: 2021/10/19 15:29:59 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHER_H
#define FT_PHILOSOPHER_H
/*
** libraries
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define FAILURE -1
#define SUCCESS 0

typedef enum s_bool
{
    FALSE,
    TRUE
} t_bool;

/*
** Structures
*/
typedef struct s_philo
{
    int                 id;
    pthread_t           *td;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     *right_fork;
    struct s_philo      *next;
} t_philo;

typedef struct s_data
{
    int             nb_philo;
    t_bool          optionnal;
    int             ttd;
    int             tte;
    int             tts;
    pthread_mutex_t print_mutex;
    t_philo         *first;
} t_data;

/*
** functions
*/
t_data *init_data(int argc, char **argv);
int ft_strlen(char *str);
int create_philo_threads(t_data *data, int philo_nb);
void *affect_forks(void *ptr);
int ft_free_all(t_data *data);

#endif