/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:58:20 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:21 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	wait_all_threads(t_program *program)
{
	while (!get_bool(&program->program_mutex, &program->all_threads_ready))
		;
}

void	de_synchronise_philos(t_philo *philo)
{
	if (philo->program->n_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(3e4, philo->program);		
	}
	else
	{
		if (philo->id % 2)	
			thinking(philo, true);
	}
}

bool	simulation_finished(t_program *program)
{
	return (get_bool(&program->program_mutex, &program->end_simulation));
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long n_philo)
{
	bool	ret;
	int		status;

	ret = false;
	status = pthread_mutex_lock(mutex);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");	
	if (*threads == n_philo)
		ret = true;
	status = pthread_mutex_unlock(mutex);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	return (ret);
}
