/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_setd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:39:20 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/05 17:56:54 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	msg_philos("is sleeping", philo, philo->id);
	ft_sleep(philo->sim->sleep_time, philo->sim);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	msg_philos("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->left_fork);
	msg_philos("has taken a fork", philo, philo->id);
	philo->eating = true;
	msg_philos("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->sim->eat_lock);
	philo->last_meal = get_current_time();
	philo->num_meals += 1;
	pthread_mutex_unlock(&philo->sim->eat_lock);
	ft_sleep(philo->sim->eat_time, philo->sim);
	philo->eating = false;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	thinking(t_philo *philo)
{
	long	tt_think;

	if ((philo->sim->num_philos % 2) != 0)
	{
		tt_think = philo->sim->eat_time * 2 - philo->sim->sleep_time;
		if (tt_think < 0)
			tt_think = 0;
		ft_sleep(tt_think, philo->sim);
	}
	msg_philos("is thinking", philo, philo->id);
}

int	dying(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->sim->dead_lock);
	if (philo->sim->dead == true)
		is_dead = 1;
	else
		is_dead = 0;
	pthread_mutex_unlock(&philo->sim->dead_lock);
	return (is_dead);
}

void	*philo(void *arg)
{
	t_philo	*philo_data;

	philo_data = (t_philo *)arg;
	philo_data->start_time = get_current_time();
	if (philo_data->sim->num_philos == 1)
	{
		pthread_mutex_lock(philo_data->left_fork);
		msg_philos("has taken a fork", philo_data, philo_data->id);
		ft_sleep(philo_data->sim->die_time, philo_data->sim);
		pthread_mutex_unlock(philo_data->left_fork);
		return (NULL);
	}
	if (philo_data->id % 2 != 0)
		ft_sleep(philo_data->sim->eat_time, philo_data->sim);
	while (philo_data->sim->dead == false)
	{
		eating(philo_data);
		sleeping(philo_data);
		thinking(philo_data);
	}
	return (NULL);
}
