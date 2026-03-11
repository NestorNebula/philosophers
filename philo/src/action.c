/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:59:36 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 11:51:30 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"

#define MAX_MSG_LEN 100
#define MAX_LONG_LEN 20

/* TODO Check state before printing */

static void	str_from_long(long l, char *str);

static void copy_string(char *dest, const char *src);

static int	copy_action(t_action action, char *msg);

int	print_action(t_action action, long time, t_philo *philo)
{
	char	msg[MAX_MSG_LEN + 1];
	size_t	msg_len;
	bool	running;

	if (philo == NULL)
		return (1);
	msg_len = 0;
	msg[msg_len] = '\0';
	str_from_long((time - philo->context->start) / 1000, msg + msg_len);
	while (msg[msg_len] != '\0')
		msg_len++;
	msg[msg_len++] = ' ';
	str_from_long(philo->number, msg + msg_len);
	while (msg[msg_len] != '\0')
		msg_len++;
	if (copy_action(action, msg + msg_len) != 0)
		return (1);
	while (msg[msg_len] != '\0')
		msg_len++;
	get_running(philo->context, &running);
	if (running)
		return (write(STDOUT_FILENO, msg, msg_len) != (int) msg_len);
	return (0);
}

static void	str_from_long(long l, char *str)
{
	char	nbr_str[MAX_LONG_LEN + 1];
	size_t	nbr_str_len;

	if (l == 0)
	{
		*str++ = '0';
		*str = '\0';
		return ;
	}
	nbr_str_len = 0;
	if (l < 0)
		*str++ = '-';
	while (l != 0 )
	{
		nbr_str[nbr_str_len++] = '0' + (l % 10);
		l /= 10;
	}
	while (nbr_str_len-- > 0)
		*str++ = nbr_str[nbr_str_len];
	*str = '\0';
	return ;
}

static void copy_string(char *dest, const char *src)
{
	size_t	i;

	if (src == NULL || dest == NULL)
		return ;
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	copy_action(t_action action, char *msg)
{
	if (action == A_FORK)
		copy_string(msg, " has taken a fork\n");
	else if (action == A_EATING)
		copy_string(msg, " is eating\n");
	else if (action == A_SLEEPING)
		copy_string(msg, " is sleeping\n");
	else if (action == A_THINKING)
		copy_string(msg, " is thinking\n");
	else if (action == A_DIED)
		copy_string(msg, " died\n");
	else
		return (1);
	return (0);
}
