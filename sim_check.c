/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:13:40 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/05 18:57:24 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_all_ate(t_simulation *sim)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if (sim->nb_eat_times == -1)
		return (0);
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->eat_lock);
		if (sim->philo[i].num_meals < sim->nb_eat_times)
			all_ate = 0;
		pthread_mutex_unlock(&sim->eat_lock);
		i++;
	}
	return (all_ate);
}

int	meal_time(t_simulation *sim)
{
	t_philo			*philo_d;
	int				i;
	unsigned int	rn;

	i = 0;
	pthread_mutex_lock(&sim->eat_lock);
	while (i < sim->num_philos)
	{
		rn = get_current_time();
		if (rn - philo_d[i].last_meal
			>= sim->die_time && !philo_d[i].eating)
		{
			msg_philos("died", &philo_d[i], philo_d[i].id);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->at_lock);
	return (0);
}

void	dead_check(t_simulation *sim)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&sim->dead_lock);
	while (!sim->dead)
	{
		pthread_mutex_unlock(&sim->dead_lock);
		if (meal_time(sim) || if_all_ate(sim))
		{
			pthread_mutex_lock(&sim->dead_lock);
			sim->dead = true;
			pthread_mutex_unlock(&sim->dead_lock);
			dead = 1;
		}
		pthread_mutex_lock(&sim->dead_lock);
	}
	pthread_mutex_unlock(&sim->dead_lock);
}
