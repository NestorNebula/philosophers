/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:34:18 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/13 09:40:00 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "context.h"
#include "master.h"
#include "action.h"
#include "utils.h"

static int	check_philos(t_master *master);

static int	check_philo(t_master *master, t_philo *philo, size_t *reached);

void	*master_routine(void *arg)
{
	t_master	*master;

	master = arg;
	if (master == NULL)
		return (NULL);
	if (master->context.meal_target == -1)
		ft_usleep(master->context.time_to_die * 1000);
	while (check_philos(master) == 0)
			ft_usleep(1000);
	set_running(&master->context, false);
	return (NULL);
}

static int	check_philos(t_master *master)
{
	size_t	reached;
	size_t	i;
	bool	stop;

	reached = 0;
	i = 0;
	stop = false;
	while (i < master->philos_size && !stop)
	{
		stop = check_philo(master, master->philos + i, &reached) != 0;
		i++;
	}
	return (stop || reached == master->philos_size);
}

static int	check_philo(t_master *master, t_philo *philo, size_t *reached)
{
	size_t	meal_count;
	long	last_meal;

	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	last_meal = philo->last_meal;
	meal_count = philo->meal_count;
	pthread_mutex_unlock(&philo->mutex);
	if (time_now() - last_meal > master->context.time_to_die * 1000)
	{
		act(A_DIED, philo);
		return (1);
	}
	if (master->context.meal_target > 0
		&& (int) meal_count >= master->context.meal_target)
		(*reached)++;
	return (0);
}
