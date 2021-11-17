/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <e.djavid@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:38:26 by edjavid           #+#    #+#             */
/*   Updated: 2021/10/20 17:38:27 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

void print_tms(t_philo *clone)
{
	pthread_mutex_lock(&clone->data->print_action);
	printf(YELLOW "\n%ld ms\n" END,
		   (actual_time() - clone->initial_time));
	pthread_mutex_unlock(&clone->data->print_action);
}

int ft_strlen(char *str)
{
	int i;

	if (!str)
		return (FAILURE);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

long int actual_time(void)
{
	long int time;
	struct timeval current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		printf("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

void ft_usleep(long int time_in_ms)
{
	long int start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}