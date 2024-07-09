/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:13:40 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/08 19:56:55 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_all_ate(t_simulation *sim)
{
	int		i;
	int		all_ate;
	t_philo	*philo_d;

	i = 0;
	all_ate = 0;
	philo_d = sim->philo;
	if (sim->nb_eat_times == -1)
		return (0);
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->eat_lock);
		if (philo_d[i].num_meals >= sim->nb_eat_times)
			all_ate++;
		pthread_mutex_unlock(&sim->eat_lock);
		i++;
	}
	if (all_ate == sim->num_philos)
		return (1);
	return (0);
}

int	meal_time(t_simulation *sim)
{
	t_philo			*philo_d;
	int				i;
	unsigned int	rn;

	i = 0;
	philo_d = sim->philo;
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->eat_lock);
		rn = get_current_time();
		if (rn - philo_d[i].last_meal
			>= sim->die_time && !philo_d[i].eating)
		{
			pthread_mutex_unlock(&sim->eat_lock);
			msg_philos("died", &philo_d[i], philo_d[i].id);
			return (1);
		}
		pthread_mutex_unlock(&sim->eat_lock);
		i++;
	}
	return (0);
}

void	check_if_dead(t_simulation *sim)
{
	pthread_mutex_lock(&sim->dead_lock);
	while (!sim->dead)
	{
		pthread_mutex_unlock(&sim->dead_lock);
		if (meal_time(sim) || if_all_ate(sim))
		{
			pthread_mutex_lock(&sim->dead_lock);
			sim->dead = true;
			pthread_mutex_unlock(&sim->dead_lock);
			break ;
		}
		pthread_mutex_lock(&sim->dead_lock);
	}
	pthread_mutex_unlock(&sim->dead_lock);
}

int	start(t_simulation *sim)
{
	int		i;
	t_philo	*philo_d;

	i = 0;
	while (i < sim->num_philos)
	{
		philo_d = &sim->philo[i];
		if (pthread_create(&philo_d->thread, NULL, &philo, philo_d) != 0)
		{
			finished(sim, true);
			return (error_msg("in threads"));
		}
		i++;
	}
	check_if_dead(sim);
	i = 0;
	while (i < sim->num_philos)
	{
		philo_d = &sim->philo[i];
		if (pthread_join(philo_d->thread, NULL) != 0)
			return (finished(sim, true), error_msg("in threads"));
		i++;
	}
	finished(sim, true);
	return (0);
}
