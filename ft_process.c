/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:19:37 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/25 22:52:50 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

int	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_philo_dead == TRUE)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_action);
	printf("%ld Philosopher %d %s\n", actual_time() - philo->data->initial_time,
		philo->id, action);
	pthread_mutex_unlock(&philo->data->print_action);
	return (SUCCESS);
}

int	ft_sleep_think(t_philo *clone)
{
	pthread_mutex_lock(&clone->data->eat_mutex);
	clone->start_eating = TRUE;
	pthread_mutex_unlock(&clone->data->eat_mutex);
	clone->nb_eat++;
	print_action(clone, PINK"started sleeping"END);
	if (clone->data->ttd < clone->data->tts)
	{
		ft_usleep(clone->data->ttd);
		print_action(clone, RED "died" END);
		is_philo_dead(clone->data, TRUE);
		return (FAILURE);
	}
	if (clone->data->optionnal == TRUE
		&& clone->nb_eat == clone->data->cycle)
		return (FAILURE);
	clone->has_slept = TRUE;
	ft_usleep(clone->data->tts);
	print_action(clone, YELLOW "started thinking"END);
	return (SUCCESS);
}

void	ft_fork_eat(t_philo *clone)
{
	pthread_mutex_lock(clone->right_fork);
	print_action(clone, CYAN "has taken a fork"END);
	pthread_mutex_lock(&clone->data->eat_mutex);
	clone->start_eating = TRUE;
	clone->eaten_time = actual_time();
	pthread_mutex_unlock(&clone->data->eat_mutex);
	print_action(clone, BLUE "started eating" END);
	if (clone->data->ttd < clone->data->tte)
	{
		ft_usleep(clone->data->ttd);
		print_action(clone, RED "died" END);
		is_philo_dead(clone->data, TRUE);
	}
	ft_usleep(clone->data->tte);
	pthread_mutex_unlock(clone->right_fork);
	pthread_mutex_unlock(&clone->left_fork);
}

int	ft_eating_time(t_philo *clone)
{
	pthread_mutex_lock(&clone->left_fork);
	print_action(clone, CYAN"has taken a fork"END);
	if (!clone->right_fork)
	{
		ft_usleep(clone->data->ttd);
		print_action(clone, RED "died" END);
		pthread_mutex_unlock(&clone->left_fork);
		is_philo_dead(clone->data, TRUE);
		return (FAILURE);
	}
	ft_fork_eat(clone);
	return (SUCCESS);
}

void	*ft_live(void *philo)
{
	t_philo	*clone;

	clone = (t_philo *)philo;
	if (clone->id % 2 == 0)
		ft_usleep(clone->data->tte / 10);
	pthread_create(&clone->death, NULL, death_upcoming, (void *)clone);
	while (is_philo_dead(clone->data, FALSE) == FALSE)
	{
		if ((clone->start_eating == FALSE)
			&& (ft_eating_time(clone) == FAILURE))
			return (NULL);
		if ((clone->has_slept == FALSE) && (ft_sleep_think(clone) == FAILURE))
			return (NULL);
		pthread_mutex_lock(&clone->data->sleep_think_mutex);
		if (clone->start_eating && clone->has_slept)
		{
			clone->start_eating = FALSE;
			clone->has_slept = FALSE;
		}
		pthread_mutex_unlock(&clone->data->sleep_think_mutex);
	}
	pthread_exit(NULL);
}
