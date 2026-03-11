/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:26:13 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 10:42:52 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "master.h"

#define MIN_ARGS 5
#define MAX_ARGS 6

static int	usage(void);

int	main(int argc, char **argv)
{
	t_master	master;

	if (argc < MIN_ARGS || argc > MAX_ARGS)
		return (usage());
	if (init_master(&master, (size_t) argc - 1, argv + 1) != 0)
		return (1);
	master_routine(&master);
	clear_master(&master);
	return (0);
}

static int	usage(void)
{
	const char	*msg = "usage: ./philo number_of_philosophers time_to_die "
		"time_to_eat time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]\n";
	size_t		i;

	i = 0;
	while (msg[i] != '\0')
		i++;
	write(STDERR_FILENO, msg, i);
	return (0);
}
