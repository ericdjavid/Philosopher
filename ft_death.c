/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <e.djavid@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:06:58 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/27 13:47:48 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

t_bool	is_philo_dead(t_data *data, t_bool is_dead)
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

void	ft_die(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->sleep_think_mutex);
	pthread_mutex_unlock(&philo->data->eat_mutex);
	print_action(philo, RED "died" END);
	is_philo_dead(philo->data, TRUE);
	pthread_exit(NULL);
}

void	*death_upcoming(void *phil)
{
	t_philo		*philo;
	long int	delta_eaten_time;

	philo = (t_philo *)phil;
	while (is_philo_dead(philo->data, FALSE) == FALSE)
	{
		ft_usleep(philo->data->ttd + 1);
		if ((philo->data->optionnal) && (philo->nb_eat == philo->data->cycle))
			pthread_exit(NULL);
		pthread_mutex_lock(&philo->data->eat_mutex);
		delta_eaten_time = actual_time() - philo->eaten_time;
		pthread_mutex_lock(&philo->data->sleep_think_mutex);
		if (((delta_eaten_time) >= philo->data->ttd
				&& philo->start_eating == FALSE)
			|| (philo->data->ttd < (philo->data->tts + philo->data->tte)))
			ft_die(philo);
		pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_mutex_unlock(&philo->data->sleep_think_mutex);
	}
	pthread_exit(NULL);
}
