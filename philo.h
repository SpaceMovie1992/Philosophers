/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:40:10 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/07 14:58:38 by ahusic           ###   ########.fr       */
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

int				error_msg(char *msg);
void			finished(t_simulation *sim, bool all);
void			msg_philos(char *msg, t_philo *philo, int id);

int				philo_init(t_simulation *sim);
int				forks_init(t_simulation *sim);

int				args_init(int argc, char **argv, t_simulation *sim);
int				args_check(int argc, char **argv);

void			sleeping(t_philo *philo);
void			eating(t_philo *philo);
void			thinking(t_philo *philo);
int				dying(t_philo *philo);
void			*philo(void *arg);

int				if_all_ate(t_simulation *sim);
int				meal_time(t_simulation *sim);
void			check_if_dead(t_simulation *sim);
int				start(t_simulation *sim);

int				main(int argc, char **argv);

#endif
