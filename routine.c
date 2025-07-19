/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:01:38 by mmutsulk          #+#    #+#             */
/*   Updated: 2025/07/16 16:06:13 by mmutsulk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_data *simul)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&simul->dead);
	i = simul->philo_is_dead;
	pthread_mutex_unlock(&simul->dead);
	return (i);
}

void	*thread_routine(void *philosoph)
{
	t_phi	*phi;

	phi = (t_phi *)philosoph;
	while (!check_death(phi->data) && !check_full_meal(phi))
	{
		lock_forks(phi);
		message(phi, "has taken a fork");
		message(phi, "has taken a fork");
		message(phi, "is eating");
		pthread_mutex_lock(&phi->data->meal);
		phi->last_eat = get_current_time(phi);
		phi->n_eat++;
		pthread_mutex_unlock(&phi->data->meal);
		ft_usleep(phi->t_eat, phi->data);
		unlock_forks(phi);
		message(phi, "is sleeping");
		ft_usleep(phi->t_sleep, phi->data);
		message(phi, "is thinking");
		thinking(phi);
	}
	return (NULL);
}

void	thinking(t_phi *phi)
{
	if (phi->n_philo % 2)
	{
		ft_usleep((phi->t_eat - phi->t_sleep + 5), phi->data);
	}
}

void	lock_forks(t_phi *phi)
{
	if (phi->id_philo % 2)
	{
		pthread_mutex_lock(phi->lf);
		pthread_mutex_lock(phi->rf);
	}
	else
	{
		pthread_mutex_lock(phi->rf);
		pthread_mutex_lock(phi->lf);
	}
}

void	unlock_forks(t_phi *phi)
{
	if (phi->id_philo % 2)
	{
		pthread_mutex_unlock(phi->rf);
		pthread_mutex_unlock(phi->lf);
	}
	else
	{
		pthread_mutex_unlock(phi->lf);
		pthread_mutex_unlock(phi->rf);
	}
}
