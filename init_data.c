/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:01:48 by mmutsulk          #+#    #+#             */
/*   Updated: 2025/07/16 16:05:06 by mmutsulk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init(int argc, char **argv, t_data *simul)
{
	simul->philo_is_dead = 0;
	simul->meal_finish = 0;
	simul->n_philo = ft_atoi(argv[1]);
	simul->t_die = ft_atoi(argv[2]);
	simul->t_eat = ft_atoi(argv[3]);
	simul->t_sleep = ft_atoi(argv[4]);
	if (simul->n_philo < 1 || simul->t_die < 1 || simul->t_eat < 1
		|| simul->t_sleep < 1)
		return (0);
	if (argc == 6)
	{
		simul->max_eat = ft_atoi(argv[5]);
		if (simul->max_eat < 1)
			return (0);
	}
	else
	{
		simul->max_eat = -1;
	}
	if (simul->n_philo == 1)
	{
		solo(simul);
		return (0);
	}
	return (1);
}

void	solo(t_data *simul)
{
	printf("0 1 has taken a fork\n");
	usleep(simul->t_die * 1000);
	printf("%d 1 died\n", (simul->t_die + 1));
}

int	init_philo_mutex(t_data *simul)
{
	int	philo_idx;

	philo_idx = 0;
	simul->phi = malloc(sizeof(t_phi) * simul->n_philo);
	if (!simul->phi)
		return (0);
	simul->mutex = malloc(sizeof(pthread_mutex_t) * simul->n_philo);
	if (!simul->mutex)
		return (0);
	while (philo_idx < simul->n_philo)
	{
		if (pthread_mutex_init(&(simul->mutex[philo_idx]), NULL))
			return (0);
		philo_idx++;
	}
	if (pthread_mutex_init(&(simul->print), NULL))
		return (0);
	if (pthread_mutex_init(&(simul->dead), NULL))
		return (0);
	if (pthread_mutex_init(&(simul->meal), NULL))
		return (0);
	link_philo(simul);
	return (1);
}

void	link_philo(t_data *simul)
{
	int	p_id;

	p_id = 0;
	while (p_id < simul->n_philo - 1)
	{
		simul->phi[p_id].lf = &simul->mutex[p_id];
		simul->phi[p_id].rf = &simul->mutex[p_id + 1];
		p_id++;
	}
	simul->phi[p_id].lf = &simul->mutex[p_id];
	simul->phi[p_id].rf = &simul->mutex[0];
}

void	init_philo(t_data *simul)
{
	int	p_id;

	p_id = 0;
	while (p_id < simul->n_philo)
	{
		simul->phi[p_id].id_philo = p_id + 1;
		simul->phi[p_id].last_eat = 0;
		simul->phi[p_id].n_eat = 0;
		simul->phi[p_id].data = simul;
		simul->phi[p_id].n_philo = simul->n_philo;
		simul->phi[p_id].t_die = simul->t_die;
		simul->phi[p_id].t_eat = simul->t_eat;
		simul->phi[p_id].t_sleep = simul->t_sleep;
		simul->phi[p_id].max_eat = simul->max_eat;
		simul->phi[p_id].t_start = simul->t_start;
		p_id++;
	}
}
