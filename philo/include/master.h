/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 08:31:47 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/08 08:41:33 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASTER_H
# define MASTER_H

# include "philo.h"

/**
 * Initializes a master structure using arguments.
 *
 * @param master A pointer to the master structure to initialize
 * @param args_size The size of the arguments array
 * @param args An array storing the arguments to use for master initialization
 * @return 0 on success, > 0 on error
 */
int	init_master(t_master *master, size_t args_size, char **args);

/**
 * Clears the content inside a master structure.
 *
 * @param master A pointer to the master structure to clear
 * @return 0 on success, > 0 on error
 */
int	clear_master(t_master *master);

#endif // !MASTER_H
