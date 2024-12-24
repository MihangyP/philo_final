/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:54 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:55 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	deep_write_status(int status, long elapsed, t_philo *philo)
{
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && 
		!simulation_finished(philo->program))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->program))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->program))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->program))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
}

void	write_status(int status, t_philo *philo)
{
	long	elapsed;
	int		s;

	elapsed = gettime('M') - philo->program->start_simulation;
	if (philo->full)
		return ;
	s = pthread_mutex_lock(&philo->program->write_mutex);
	if (s != 0)
		print_error_and_exit("cannot lock mutex");
	deep_write_status(status, elapsed, philo);
	s = pthread_mutex_unlock(&philo->program->write_mutex);
	if (s != 0)
		print_error_and_exit("cannot unlock mutex");
}
