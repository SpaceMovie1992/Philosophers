/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:40:10 by ahusic            #+#    #+#             */
/*   Updated: 2024/06/25 19:47:28 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_simulation
{
	int				num_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nb_eat_times;
	bool			dead;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
}							t_simulation;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			eating;
	long			num_meals;
	long			last_meal;
	long			start_time;
	t_simulation	*sim;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}							t_philo;

int				ft_strlen(const char *str);
int				is_digit(const char *str);
int				ft_atoi(const char *str);

unsigned int	get_current_time(void);
void			ft_sleep(unsigned int time, t_simulation *sim);

int				erorr_msg(char *msg);

#endif
