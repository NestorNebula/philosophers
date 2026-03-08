/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 08:26:11 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/08 08:38:05 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <pthread.h>
# include <stdbool.h>

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

/**
 * Initializes a context structure using arguments.
 *
 * @param context A pointer to a context structure
 * @param args_size The size of the arguments array
 * @param args An array storing the arguments to use for context initialization
 * @return 0 on success, > 0 on error
 */
int	init_context(t_context *context, size_t args_size, char **args);

/**
 * Sets the running status of the given context to false.
 *
 * @param context A pointer to a context structure
 * @return 0 on success, > 0 on error
 */
int	stop_context(t_context *context);

/**
 * Clears the content inside a context structure.
 *
 * @param context A pointer to the context structure to clear
 * @return 0 on success, > 0 on error
 */
int	clear_context(t_context *context);

#endif // !CONTEXT_H
