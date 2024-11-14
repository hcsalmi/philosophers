/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:36:29 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:36:31 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data)
{
	int	i;

	i = data->tot_philo - 1;
	while (i >= 0)
	{
		pthread_join(data->party[i].t_id, NULL);
		i--;
	}
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->gate);
	while (i < data->tot_philo)
	{
		if (pthread_mutex_init(&data->party[i].food_mutex, NULL) != 0)
			return (error(4, data));
		init_each_philo(data, i);
		if (pthread_create(&data->party[i].t_id, NULL,
				(void *)routine, ((void *) &(data->party[i]))) != 0)
		{
			pthread_mutex_lock(&data->check_death);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->check_death);
			pthread_mutex_unlock(&data->gate);
			return (error(3, data));
		}
		i++;
	}
	data->start = get_time();
	pthread_mutex_unlock(&data->gate);
	monitor_status(data);
	return (0);
}
