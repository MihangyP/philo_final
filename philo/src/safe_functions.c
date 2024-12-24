/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:38 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:39 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*safe_malloc(size_t	bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		print_error_and_exit("Error with the malloc\n");
	return (res);
}

void	safe_mutex_handle(pthread_mutex_t *mutex, int opcode)
{
	if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			print_error_and_exit("cannot lock mutex");
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			print_error_and_exit("cannot unlock mutex");
	}
	else if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			print_error_and_exit("cannot init mutex");
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			print_error_and_exit("cannot destroy mutex");
	}
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, int opcode)
{
	if (opcode == CREATE)
	{
		if (pthread_create(thread, NULL, foo, data) != 0)
			print_error_and_exit("cannot create thread");
	}
	else if (opcode == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			print_error_and_exit("cannot join thread");
	}
}
