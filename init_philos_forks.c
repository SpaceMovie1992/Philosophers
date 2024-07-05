/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:22:01 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/01 19:04:37 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_simulation *sim)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * sim->num_philos);
	if (philo == NULL)
		return (1);
	sim->philo = philo;
	i = 0;
	while (i < sim->num_philos)
	{
		philo[i].sim = sim;
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].num_meals = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].right_fork = &sim->forks[i];
		if (i == sim->num_philos - 1)
			philo[i].left_fork = &sim->forks[0];
		else
			philo[i].left_fork = &sim->forks[i + 1];
		i++;
	}
	return (0);
}

int	forks_init(t_simulation *sim)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * sim->num_philos);
	if (forks == NULL)
		return (1);
	sim->forks = forks;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (1);
		}
		i++;
	}
	return (0);
}
