/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:02:21 by mmutsulk          #+#    #+#             */
/*   Updated: 2025/07/16 16:06:28 by mmutsulk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + (nptr[i] - 48);
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	return (r * s);
}

long	get_start_time(t_data *simul)
{
	struct timeval	tmp;

	(void)simul;
	gettimeofday(&tmp, NULL);
	return ((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000));
}

long long	get_current_time(t_phi *phi)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	return (((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000)) - phi->t_start);
}

void	ft_usleep(int i, t_data *simul)
{
	int	a;

	a = 0;
	while (a < i && !check_death(simul))
	{
		usleep(10000);
		a += 10;
	}
}

void	message(t_phi *phi, char *str)
{
	if (!check_death(phi->data))
	{
		pthread_mutex_lock(&(phi->data->print));
		printf("%lld %d %s\n", get_current_time(phi), phi->id_philo, str);
		pthread_mutex_unlock(&(phi->data->print));
	}
}
