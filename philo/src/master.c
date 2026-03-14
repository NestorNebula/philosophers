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
#include <unistd.h>
#include "master.h"
#include "utils.h"

#define ARGS_MIN 4
#define ARGS_MAX 5
#define ERR_MSG "Invalid arguments\n"
#define ERR_MSG_LEN 18

static int	init_from_args(t_master *master, char **args);

static int	init_philos_and_forks(t_master *master);

static void	clear_philos_and_forks(t_master *master, size_t philos_count,
				size_t forks_count);

int	init_master(t_master *master, size_t args_size, char **args)
{
	long	time;

	if (master == NULL || args == NULL
		|| args_size < ARGS_MIN || args_size > ARGS_MAX)
		return (1);
	if (init_from_args(master, args) != 0)
	{
		write(STDERR_FILENO, ERR_MSG, ERR_MSG_LEN);
		return (1);
	}
	if (init_context(&master->context, args_size - 1, args + 1) != 0)
		return (1);
	master->philos = malloc(master->philos_size * sizeof(t_philo));
	master->forks = malloc(master->philos_size * sizeof(t_fork));
	if (master->philos == NULL || master->forks == NULL
		|| init_philos_and_forks(master) != 0)
	{
		free(master->philos);
		free(master->forks);
		clear_context(&master->context);
		return (1);
	}
	time = time_now();
	set_start(&master->context, time);
	return (0);
}

int	clear_master(t_master *master)
{
	clear_philos_and_forks(master, master->philos_size, master->philos_size);
	clear_context(&master->context);
	free(master->philos);
	free(master->forks);
	return (0);
}

static int	init_from_args(t_master *master, char **args)
{
	int		philos_number;
	bool	err;

	err = false;
	philos_number = int_from_str(args[0], &err);
	if (err || philos_number <= 0)
		return (1);
	master->philos_size = philos_number;
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
		{
			err = true;
			clear_philos_and_forks(master, i, i);
		}
		else if (init_fork(&master->forks[i]) != 0)
		{
			err = true;
			clear_philos_and_forks(master, i + 1, i);
		}
		i++;
	}
	if (!err)
		return (0);
	set_running(&master->context, false);
	return (err);
}

static void	clear_philos_and_forks(t_master *master, size_t philos_count,
				size_t forks_count)
{
	size_t	i;

	i = 0;
	while (i < philos_count)
		clear_philo(&master->philos[i++]);
	i = 0;
	while (i < forks_count)
		clear_fork(&master->forks[i++]);
}
