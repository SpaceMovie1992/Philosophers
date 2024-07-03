/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:42:40 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/03 13:05:46 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_init(int argc, char **argv, t_simulation *sim)
{
	sim->num_philos = ft_atoi(argv[1]);
	sim->die_time = ft_atoi(argv[2]);
	sim->eat_time = ft_atoi(argv[3]);
	sim->sleep_time = ft_atoi(argv[4]);
	sim_dead = false;
	sim->nb_eat_times = -1;
	if (argc == 6)
		sim->nb_eat_times = ft_atoi(argv[5]);
	if (pthread_mutex_init(&sim->dead_lock, NULL)
		|| pthread_mutex_init(&sim->print_lock, NULL)
		|| pthread_mutex_init(&sim->eat_lock, NULL))
		return (1);
	if (forks_init(sim) || philo_init(sim))
		return (1);
	return (0);
}

int	args_check(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (1);
	if (ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[1]) < 60)
		return (1);
	if (ft_atoi(argv[2]) < 60)
		return (1);
	if (ft_atoi(argv[3]) < 60)
		return (1);
	if (ft_atoi(argv[4]) < 60)
		return (1);
	return (0);
}
