/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <e.djavid@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:38:26 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/25 22:15:55 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (FAILURE);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		printf("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

int	get_values(char *str)
{
	int					i;
	long long unsigned	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FAILURE);
		nb *= 10;
		nb = nb + ((str[i] - '0'));
		i++;
	}
	if (nb >= INT_MAX)
		return (INT_MAX - 1);
	return (nb);
}
