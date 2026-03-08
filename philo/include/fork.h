/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 08:35:14 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/08 08:37:59 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

/**
 * Initializes a fork structure.
 *
 * @param fork A pointer to the fork structure to initialize
 * @return 0 on success, > 0 on error
 */
int	init_fork(t_fork *fork);

/**
 * Clears the content inside a fork structure.
 *
 * @param fork A pointer to the fork structure to clear
 * @return 0 on success, > 0 on error
 */
int	clear_fork(t_fork *fork);

#endif // !FORK_H
