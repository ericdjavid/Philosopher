/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <e.djavid@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:20:13 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/27 13:15:53 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

t_bool	new_philo(t_philo *first, int nb)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = malloc(sizeof(*philo));
	if (!philo || !first)
		return (FAILURE);
	tmp = first;
	philo->id = nb;
	philo->start_eating = FALSE;
	philo->has_think = FALSE;
	philo->has_slept = FALSE;
	philo->data = first->data;
	philo->eaten_time = 0;
	philo->nb_eat = 0;
	pthread_mutex_init(&philo->left_fork, NULL);
	philo->right_fork = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = philo;
	philo->next = NULL;
	return (SUCCESS);
}

int	add_philo_chain(int philo_nb, t_philo *first)
{
	t_philo	*tmp;
	int		i;

	i = 1;
	tmp = first;
	while (i++ < philo_nb)
		new_philo(first, i);
	while (tmp->next)
	{
		tmp->right_fork = &tmp->next->left_fork;
		tmp = tmp->next;
	}
	if (philo_nb > 1)
		tmp->right_fork = &first->left_fork;
	return (SUCCESS);
}

int	create_philo_threads(t_data *data)
{
	t_philo	*first;
	t_philo	*tmp;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (init_philo(data))
		return (FAILURE);
	first = data->first;
	add_philo_chain(data->nb_philo, first);
	tmp = first;
	data->initial_time = actual_time();
	while (i < data->nb_philo)
	{
		ret = pthread_create(&tmp->td, NULL, ft_live, (void *)tmp);
		if (ret != 0)
		{
			printf("Error : issue while thread creation");
			return (FAILURE);
		}
		tmp = tmp->next;
		i++;
	}
	return (SUCCESS);
}

void	init_data2(t_data *data)
{
	data->is_philo_dead = FALSE;
	data->initial_time = 0;
	pthread_mutex_init(&data->print_action, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->sleep_think_mutex, NULL);
	if (data->tte > data->ttd)
		data->tte = data->ttd + 1;
	if (data->tts > data->ttd)
		data->tts = data->ttd + 1;
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (data == NULL)
		return (NULL);
	data->optionnal = FALSE;
	if (argc == 6)
		data->optionnal = TRUE;
	data->nb_philo = get_values(argv[1]);
	data->ttd = get_values(argv[2]);
	data->tte = get_values(argv[3]);
	data->tts = get_values(argv[4]);
	data->cycle = 0;
	if (data->optionnal == TRUE)
		data->cycle = get_values(argv[5]);
	if (data->nb_philo == 0 || data->nb_philo == FAILURE
		|| data->ttd == FAILURE || data->tte == FAILURE || data->tts == FAILURE
		|| data->cycle == FAILURE || data->ttd == 0)
	{
		printf(RED "Argument error\n" END);
		free(data);
		return (NULL);
	}
	init_data2(data);
	return (data);
}
