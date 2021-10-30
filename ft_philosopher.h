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

typedef struct s_data
{
    int nb_philo;
    t_bool optionnal;
    int ttd;
    int tte;
    int tts;

} t_data;

t_data *init_data(int argc, char **argv);
int ft_strlen(char *str);
int create_philo_threads(int philo_nb);
int init_thread(pthread_t id);
void* print_created(void *ptr);

#endif