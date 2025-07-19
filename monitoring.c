/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:01:44 by mmutsulk          #+#    #+#             */
/*   Updated: 2025/07/16 16:05:45 by mmutsulk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_die(t_data *simul)
{
	int	philo_index;
	int	all_philos_full;

	philo_index = 0;
	all_philos_full = 0;
	while (!check_death(simul))
	{
		while (philo_index < simul->n_philo)
		{
			if (!check_full_meal(&simul->phi[philo_index]))
			{
				if (norm(simul, philo_index))
				{
					ft_death(simul, philo_index);
					break ;
				}
			}
			philo_index++;
		}
		philo_index = 0;
		if (check_all_phi_meal(simul))
			return (1);
	}
	return (1);
}

int	norm(t_data *simul, int i)
{
	int	b;

	b = 0;
	pthread_mutex_lock(&simul->meal);
	if (get_current_time(&simul->phi[i])
		- simul->phi[i].last_eat > simul->phi[i].t_die)
		b = 1;
	else
		b = 0;
	pthread_mutex_unlock(&simul->meal);
	return (b);
}

void	ft_death(t_data *simul, int i)
{
	pthread_mutex_lock(&simul->dead);
	simul->philo_is_dead = 1;
	pthread_mutex_unlock(&simul->dead);
	pthread_mutex_lock(&(simul->print));
	printf("%lld %d died\n", get_current_time(&simul->phi[i]),
		simul->phi[i].id_philo);
	pthread_mutex_unlock(&(simul->print));
}

int	check_all_phi_meal(t_data *simul)
{
	int	philo_index;

	philo_index = 0;
	while (philo_index < simul->n_philo)
	{
		if (!check_full_meal(&simul->phi[philo_index]))
			break ;
		philo_index++;
	}
	if (philo_index == simul->n_philo)
		return (1);
	return (0);
}

int	check_full_meal(t_phi *phi)
{
	int	has_eaten_enough;

	pthread_mutex_lock(&phi->data->meal);
	if (phi->max_eat == -1)
		has_eaten_enough = 0;
	else if (phi->max_eat > 0 && phi->n_eat < phi->max_eat)
		has_eaten_enough = 0;
	else
	{
		phi->last_eat = 0;
		has_eaten_enough = 1;
	}
	pthread_mutex_unlock(&phi->data->meal);
	return (has_eaten_enough);
}
