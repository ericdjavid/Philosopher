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
#define PINK "\033[95m"
#define END "\033[0m"
#define YELLOW "\033[93m"
#define RED "\033[91m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"

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
    int id;
    pthread_t td;
    pthread_t death;
    pthread_mutex_t left_fork;
    pthread_mutex_t *right_fork;
    struct s_philo *next;
    t_bool start_eating;
    t_bool has_slept;
    t_bool has_think;
    struct s_data *data;
    long int initial_time;
    long int eaten_time;
} t_philo;

typedef struct s_data
{
    int nb_philo;
    t_bool optionnal;
    int ttd;
    int tte;
    int tts;
    // TODO: move mutexes to philo struct
    pthread_mutex_t print_action;
    pthread_mutex_t death_mutex;
    pthread_mutex_t eat_mutex;
    // pthread_t death;
    t_philo *first;
    t_bool is_philo_dead;
} t_data;

/*
** functions
*/
t_data *init_data(int argc, char **argv);
int ft_strlen(char *str);
int create_philo_threads(t_data *data, int philo_nb);
void *affect_forks(void *ptr);
int ft_free_all(t_data *data);
int init_philo(t_data *data);
void ft_usleep(long int time_in_ms);
long int actual_time(void);
void *ft_live(void *data);
int print_action(t_philo *philo, char *action);
t_bool reach_die(t_philo *philo, long int actual);
t_bool is_philo_dead(t_data *data, t_bool is_dead);
void print_tms(t_philo *clone);
void *death_upcoming(void *phil);
t_bool is_philo_dead(t_data *data, t_bool is_dead);

#endif