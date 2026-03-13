/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:57:50 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 09:03:33 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include "context.h"
# include "fork.h"

typedef enum e_state
{
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD,
}	t_state;

typedef struct s_philo
{
	pthread_t		thread;
	t_state			state;
	unsigned int	number;
	long			last_meal;
	size_t			meal_count;
	t_fork			*forks[2];
	t_context		*context;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_master
{
	t_philo		*philos;
	size_t		philos_size;
	t_fork		*forks;
	t_context	context;
}	t_master;

/**
 * Initializes a philo structure. 
 *
 * @param philo A pointer to the philo structure to initialize
 * @param number The number of the philo to initialize
 * @param philo_master A pointer to the master structure that will
 * handle the initialized philo structure
 * @return 0 on success, > 0 on error
 */
int		init_philo(t_philo *philo, unsigned int number, t_master *philo_master);

/**
 * The routine function for a philo thread.
 *
 * @param arg A pointer to a philo structure
 * @return A null pointer
 */
void	*philo_routine(void *arg);

/**
 * Clears the content inside a philo structure.
 *
 * @param A pointer to the philo structure to clear
 * @return 0 on success, > 0 on error
 */
int		clear_philo(t_philo *philo);

/**
 * Sets a philo's last meal to the given value.
 *
 * @param philo A pointer to a philo structure
 * @param last_meal The value to set
 * @return 0 on success, > on error
 */
int		set_last_meal(t_philo *philo, long last_meal);

/**
 * Gets a philo's last meal.
 *
 * @param philo A pointer to a philo structure
 * @param last_meal A pointer to a variable where the value can be stored
 * @return 0 on success, > 0 on error
 */
int		get_last_meal(t_philo *philo, long *last_meal);

/**
 * Sets a philo's meal count to the given value.
 *
 * @param philo A pointer to a philo structure
 * @param meal_count The value to set
 * @return 0 on success, > on error
 */
int		set_meal_count(t_philo *philo, size_t meal_count);

/**
 * Gets a philo's meal count.
 *
 * @param philo A pointer to a philo structure
 * @param meal_count A pointer to a variable where the value can be stored
 * @return 0 on success, > 0 on error
 */
int		get_meal_count(t_philo *philo, size_t *meal_count);

/**
 * Increases a philo's meal count by 1 and updates their last meal
 * 
 * @param philo A pointer to a philo structure
 * @return 0 on success, > 0 on error
 */
int		increase_meal_count(t_philo *philo);

#endif // !PHILO_H
