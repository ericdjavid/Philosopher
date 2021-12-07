/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:51:37 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/25 19:53:14 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosopher.h"

void	free_elems(t_philo *first)
{
	t_philo	*tmp;

	tmp = first;
	while (tmp)
	{
		first = first->next;
		free(tmp);
		tmp = first;
	}
}

int	ft_free_all(t_data *data)
{
	if (data->first)
		free_elems(data->first);
	if (data)
		free(data);
	return (SUCCESS);
}
