/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:35:02 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:35:07 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if (check_pulse(philo) != 0)
		return ;
	pthread_mutex_lock(&philo->data->forks[philo->fork_index_l]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->fork_index_r]);
	print_message(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->fork_index_l]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_index_r]);
}

void	eat(t_philo *philo)
{
	if (check_pulse(philo) != 0)
		return ;
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->food_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->food_mutex);
	philo->times_eaten++;
	print_message(philo, "is eating");
	ft_usleep(philo, get_time(), philo->data->time_to_eat);
}
