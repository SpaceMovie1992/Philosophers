/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:43:20 by ahusic            #+#    #+#             */
/*   Updated: 2024/06/29 05:52:42 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}


void	finished(t_simulation *sim, bool all)
{
	int	i;

	i = 0;
	if (all)
	{
		while (i < sim->num_philos)
		{
			pthread_mutex_destroy(&(sim->forks));
			i++;
		}
		pthread_mutex_destroy(&sim->dead_lock);
		pthread_mutex_destroy(&sim->print_lock);
		pthread_mutex_destroy(&sim->eat_lock);
	}
	if (sim->forks != NULL)
	{
		free(sim->forks);
		sim->forks = NULL;
	}
	if (sim->philo != NULL)
	{
		free(sim->philo);
		sim->philo = NULL;
	}
}

void	msg_philos(char *msg, t_philo *philo, int id)
{
	if (!philo->sim->dead)
	{
		pthread_mutex_lock(&philo->sim->print_lock);
		printf("%d %d %s\n", get_current_time() - philo->start_time, id, msg);
		pthread_mutex_unlock(&philo->sim->print_lock);
	}
}
