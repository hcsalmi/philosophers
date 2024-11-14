/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:36:36 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:36:40 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * (int)result);
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	sec;
	unsigned long	micro_sec;
	unsigned long	real_time;

	gettimeofday(&time, NULL);
	sec = (time.tv_sec * 1000);
	micro_sec = (time.tv_usec / 1000);
	real_time = sec + micro_sec;
	return (real_time);
}

int	ft_usleep(t_philo *philo, int start_time, int time_to_wait)
{
	int	time;

	(void)philo;
	time = get_time();
	while (time - start_time < time_to_wait)
	{
		time = get_time();
		if (check_pulse(philo) != 0)
			return (0);
		usleep(300);
	}
	return (0);
}

void	data_mutex_destroy(t_data *data)
{
	pthread_mutex_destroy(&data->status);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->gate);
	pthread_mutex_destroy(&data->check_death);
}

void	free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	if (data->party)
	{
		while (i < data->tot_philo)
		{
			pthread_mutex_destroy(&data->party[i].food_mutex);
			i++;
		}
		if (data->party)
			free(data->party);
	}
	data_mutex_destroy(data);
	while (i < data->tot_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
}
