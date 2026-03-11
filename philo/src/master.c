/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:30:13 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/09 08:31:15 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "master.h"
#include "utils.h"

#define ARGS_MIN 4
#define ARGS_MAX 5

static int	init_philos_and_forks(t_master *master);

int	init_master(t_master *master, size_t args_size, char **args)
{
	int		philos_number;
	long	time;

	if (master == NULL || args == NULL
		|| args_size < ARGS_MIN || args_size > ARGS_MAX)
		return (1);
	if (int_from_str(args[0], (int *) &philos_number) != 0
		|| init_context(&master->context, args_size - 1, args + 1) != 0)
		return (1);
	if (philos_number <= 0)
		return (1);
	master->philos_size = philos_number;
	master->philos = malloc(master->philos_size * sizeof(t_philo));
	master->forks = malloc(master->philos_size * sizeof(t_fork));
	if (master->philos == NULL || master->forks == NULL
		|| init_philos_and_forks(master) != 0)
	{
		free(master->philos);
		free(master->forks);
		return (1);
	}
	time = time_now();
	set_start(&master->context, time);
	return (0);
}

int	clear_master(t_master *master)
{
	size_t	i;

	i = 0;
	while (i < master->philos_size)
		clear_philo(&master->philos[i++]);
	i = 0;
	while (i < master->philos_size)
		clear_fork(&master->forks[i++]);
	clear_context(&master->context);
	free(master->philos);
	free(master->forks);
	return (0);
}

static int	init_philos_and_forks(t_master *master)
{
	size_t	i;
	bool	err;

	err = false;
	i = 0;
	while (i < master->philos_size && !err)
	{
		if (init_philo(&master->philos[i], i + 1, master) != 0)
			err = true;
		else if (init_fork(&master->forks[i]) != 0)
		{
			err = true;
			clear_philo(&master->philos[i]);
		}
		else
			i++;
	}
	if (!err)
		return (0);
	while (i-- > 0)
	{
		clear_philo(&master->philos[i]);
		clear_fork(&master->forks[i]);
	}
	return (err);
}
