/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:35:57 by lsalmi            #+#    #+#             */
/*   Updated: 2023/08/02 13:36:00 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define RED "\e[0;31m"
# define COLRESET "\033[1;0m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				tot_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	start;
	int				meals;
	int				finished;
	int				someone_died;
	t_philo			*party;
	pthread_mutex_t	*forks;
	pthread_mutex_t	gate;
	pthread_mutex_t	print;
	pthread_mutex_t	status;
	pthread_mutex_t	check_death;
}	t_data;

typedef struct s_philo
{
	int				idx;
	unsigned long	last_meal;
	int				times_eaten;
	int				fork_index_l;
	int				fork_index_r;
	t_data			*data;
	pthread_t		t_id;
	pthread_mutex_t	food_mutex;
}	t_philo;

int				check_args(char **argv);
int				check_pulse(t_philo *philo);
void			drop_forks(t_philo *philo);
void			eat(t_philo *philo);
int				error(int code, t_data *data);
void			free_and_destroy(t_data *data);
int				ft_usleep(t_philo *philo, int start_time, int time_to_wait);
unsigned long	get_time(void);
int				init_data(char **argv, t_data *data);
int				init_each_philo(t_data *data, int i);
int				init_philos(t_philo *philo, t_data *d);
void			join_threads(t_data *data);
void			monitor_status(t_data *data);
int				philo_atoi(const char *str);
void			pick_up_forks(t_philo *philo);
int				print_message(t_philo *philo, char *action);
void			*routine(void *ptr);
int				start_threads(t_data *data);

#endif
