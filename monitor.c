/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:35:41 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:35:45 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	have_they_had_enough(t_data *data)
{
	pthread_mutex_lock(&data->status);
	if (data->finished == data->tot_philo)
	{
		pthread_mutex_unlock(&data->status);
		return (1);
	}
	pthread_mutex_unlock(&data->status);
	return (0);
}

void	we_lost_phil(t_data *d, int i)
{
	pthread_mutex_lock(&d->check_death);
	d->someone_died = 1;
	pthread_mutex_unlock(&d->check_death);
	pthread_mutex_unlock(&d->party[i].food_mutex);
	pthread_mutex_lock(&d->print);
	printf("%s%lu %d %s\n"COLRESET"", RED,
		get_time() - d->start, d->party[i].idx, "died");
	pthread_mutex_unlock(&d->print);
	pthread_mutex_unlock(&d->party[i].data->forks[d->party[i].fork_index_l]);
	pthread_mutex_unlock(&d->party[i].data->forks[d->party[i].fork_index_r]);
}

void	monitor_status(t_data *data)
{
	int			i;

	usleep(200);
	while (1)
	{
		i = 0;
		if (data->meals > 0)
			if (have_they_had_enough(data) == 1)
				return ;
		while (i != data->tot_philo)
		{
			pthread_mutex_lock(&data->party[i].food_mutex);
			if (get_time() - data->party[i].last_meal >= data->time_to_die)
			{
				we_lost_phil(data, i);
				return ;
			}
			pthread_mutex_unlock(&data->party[i].food_mutex);
			i++;
		}
	}
}
