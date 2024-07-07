/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:48:55 by ahusic            #+#    #+#             */
/*   Updated: 2024/07/07 15:09:12 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (args_check(argc, argv))
		return (error_msg("aaa"), 1);
	if ((argc < 5 || argc > 6) || args_check(argc, argv))
		return (error_msg("wrong number of args"), 1);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (0);
	if (args_init(argc, argv, &sim) != 0)
	{
		finished(&sim, false);
		return (error_msg("in init function"), 1);
	}
	start(&sim);
	return (0);
}
