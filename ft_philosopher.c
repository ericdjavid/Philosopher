/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:29:21 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/25 22:24:23 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

int	init_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (FAILURE);
	philo->id = 1;
	philo->next = NULL;
	philo->start_eating = FALSE;
	philo->has_think = FALSE;
	philo->has_slept = FALSE;
	philo->eaten_time = 0;
	philo->nb_eat = 0;
	philo->data = data;
	philo->initial_time = 0;
	pthread_mutex_init(&philo->left_fork, NULL);
	philo->right_fork = NULL;
	data->first = philo;
	return (SUCCESS);
}

void	join_threads(t_philo *first)
{
	t_philo	*tmp;

	tmp = first;
	while (tmp->next)
	{
		tmp = tmp->next;
		(void)pthread_join(tmp->td, NULL);
		(void)pthread_join(tmp->death, NULL);
	}
	(void)pthread_join(first->td, NULL);
	(void)pthread_join(first->death, NULL);
}

void	destroy_mutex(t_philo *first)
{
	t_philo	*tmp;

	tmp = first;
	while (tmp->next)
	{
		tmp = tmp->next;
		pthread_mutex_destroy(&tmp->left_fork);
	}
	pthread_mutex_destroy(&first->left_fork);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (1);
	if (create_philo_threads(data) == FAILURE)
		return (2);
	join_threads(data->first);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->print_action);
	destroy_mutex(data->first);
	ft_free_all(data);
	return (0);
}
