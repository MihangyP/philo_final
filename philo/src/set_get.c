/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:58:15 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:16 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	int	status;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	*dest = value;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	int	status;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	*dest = value;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;
	int		status;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	ret = *value;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (ret);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;
	int		status;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	ret = *value;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (ret);
}
