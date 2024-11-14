/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:35:28 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:35:33 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(int code, t_data *data)
{
	if (code == 1)
	{
		write(2, "Wrong number of arguments\n", 26);
		printf("Usage: %s %s %s %s\nOptional: %s\n", "[number_of_philos]",
			"[time_to_die]", "[time_to_eat]", "[time_to_sleep]",
			"[number_of_times_each_philosopher_must_eat]");
	}
	if (code == 2)
		write(2, "Invalid arguments. Only positive integers allowed\n", 50);
	if (code == 3)
		write(2, "Failed to create a thread\n", 27);
	if (code == 4)
		write(2, "Mutex init error\n", 17);
	if (code == 5)
		write(2, "No room in the restaurant\n", 26);
	if (code == 3 || code == 4)
		free_and_destroy(data);
	return (-1);
}

int	print_message(t_philo *philo, char *action)
{
	long long int	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->check_death);
	if (philo->data->someone_died == 0)
		printf("%llu %d %s\n", time,
			philo->idx, action);
	pthread_mutex_unlock(&philo->data->check_death);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc < 5 || argc > 6)
	{
		error(1, &data);
		return (0);
	}
	if (init_data(argv, &data) == -1)
		return (0);
	if (start_threads(&data) == -1)
		return (-1);
	join_threads(&data);
	free_and_destroy(&data);
	return (0);
}
