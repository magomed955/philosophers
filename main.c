/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:02:12 by mmutsulk          #+#    #+#             */
/*   Updated: 2025/07/16 15:08:44 by mmutsulk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_exit(t_data *simul)
{
	int	i;

	i = 0;
	while (i < simul->n_philo)
	{
		pthread_mutex_destroy(&simul->mutex[i]);
		i++;
	}
	free(simul->mutex);
	free(simul->phi);
	pthread_mutex_destroy(&(simul->print));
	pthread_mutex_destroy(&(simul->dead));
	pthread_mutex_destroy(&(simul->meal));
}

int	init_thread(t_data *simul)
{
	int	i;

	i = 0;
	while (i < simul->n_philo)
	{
		if (pthread_create(&(simul->phi[i].th), NULL, thread_routine,
				&(simul->phi[i])))
		{
			free_exit(simul);
			return (0);
		}
		i += 2;
	}
	i = 1;
	while (i < simul->n_philo)
	{
		if (pthread_create(&(simul->phi[i].th), NULL, thread_routine,
				&(simul->phi[i])))
		{
			free_exit(simul);
			return (0);
		}
		i += 2;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	simul;
	int		i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		simul.t_start = get_start_time(&simul);
		if (init(argc, argv, &simul) == 0)
			return (0);
		if (init_philo_mutex(&simul) == 0)
			return (0);
		init_philo(&simul);
		if (init_thread(&simul) == 0)
			return (0);
		while (!check_die(&simul))
			;
		while (i < simul.n_philo)
		{
			pthread_join(simul.phi[i].th, NULL);
			i++;
		}
		free_exit(&simul);
	}
	return (0);
}
