/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmutsulk <mmutsulk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:02:17 by mmutsulk          #+#    #+#             */
/*   Updated: 2025/07/16 16:04:53 by mmutsulk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_phi
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	long long		t_start;

	int				id_philo;
	long			last_eat;
	int				n_eat;
	pthread_t		th;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	struct s_data	*data;
}					t_phi;

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	int				meal_finish;

	long long		t_start;
	long			current_time;

	int				philo_is_dead;

	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	*mutex;
	t_phi			*phi;
}					t_data;

int					ft_atoi(char *nptr);

int					init(int argc, char **argv, t_data *simul);

int					init_philo_mutex(t_data *simul);

void				init_philo(t_data *simul);

long				get_start_time(t_data *simul);

long long			get_current_time(t_phi *phi);

void				*thread_routine(void *philosoph);

void				ft_usleep(int i, t_data *simul);

void				free_exit(t_data *simul);

void				message(t_phi *phi, char *str);

void				solo(t_data *simul);

int					check_die(t_data *simul);

void				check_meal(t_data *simul);

void				lock_forks(t_phi *phi);

void				unlock_forks(t_phi *phi);

int					check_death(t_data *simul);

void				ft_death(t_data *simul, int i);

int					check_full_meal(t_phi *phi);

int					check_all_phi_meal(t_data *simul);

int					norm(t_data *simul, int i);

void				thinking(t_phi *phi);

void				link_philo(t_data *simul);

#endif
