/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:57:50 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/06 16:03:20 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>

typedef enum e_state
{
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD,
}	t_state;

typedef struct s_context
{
	bool			running;
	long			start;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_target;
	pthread_mutex_t	mutex;
}	t_context;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_state			state;
	unsigned int	number;
	long			last_meal;
	size_t			meal_count;
	t_fork			*forks[2];
	t_context		*context;
}	t_philo;

typedef struct s_master
{
	t_philo		*philos;
	size_t		philos_size;
	t_fork		*forks;
	t_context	context;
}	t_master;

#endif // !PHILO_H
