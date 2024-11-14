/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:36:18 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:36:22 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_pulse(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_death);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->check_death);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->check_death);
	return (0);
}

void	sleep_think(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo, get_time(), philo->data->time_to_sleep);
	print_message(philo, "is thinking");
}

void	open_gates(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->gate);
	pthread_mutex_lock(&philo->food_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->food_mutex);
	pthread_mutex_unlock(&philo->data->gate);
	print_message(philo, "is thinking");
	if (philo->idx % 2 == 0)
		ft_usleep(philo, get_time(), philo->data->time_to_die / 4);
}

void	*routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	open_gates(philo);
	while (1)
	{
		eat(philo);
		usleep(500);
		if (check_pulse(philo) != 0)
		{
			drop_forks(philo);
			break ;
		}
		if (philo->data->meals > 0 && philo->times_eaten == philo->data->meals)
		{
			pthread_mutex_lock(&philo->data->status);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->status);
			drop_forks(philo);
			break ;
		}
		drop_forks(philo);
		sleep_think(philo);
	}
	return (NULL);
}
