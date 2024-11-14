/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:35:13 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:35:18 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_each_philo(t_data *data, int i)
{
	data->party[i].idx = i + 1;
	data->party[i].times_eaten = 0;
	data->party[i].last_meal = get_time();
	data->party[i].data = data;
	data->party[i].fork_index_l = i;
	data->party[i].fork_index_r = (i + 1) % data->tot_philo;
	return (0);
}

int	create_party(t_data *data)
{
	int	i;

	i = 0;
	data->party = (t_philo *)malloc(sizeof(t_philo) * data->tot_philo);
	if (data->party == NULL)
		return (-1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->tot_philo);
	if (data->forks == NULL)
		return (-1);
	i = 0;
	while (i < data->tot_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	data_mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->status, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->check_death, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->gate, NULL) != 0)
		return (-1);
	return (0);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_data(char **argv, t_data *data)
{
	if (check_args(argv) == -1)
		return (error(2, data));
	data->tot_philo = philo_atoi(argv[1]);
	if (data->tot_philo > 200)
		return (error(5, data));
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	data->someone_died = 0;
	data->finished = 0;
	if (argv[5])
		data->meals = philo_atoi(argv[5]);
	else
		data->meals = -1;
	if (data->meals == 0 || data->tot_philo == 0)
		return (error(2, data));
	data->start = 0;
	if (data_mutex_init(data) != 0)
		return (error(4, data));
	create_party(data);
	return (0);
}
