/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:20 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:21 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_philo *philo)
{
	int	status;

	status = pthread_mutex_lock(&philo->first_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot lock mutex");
	write_status(TAKE_FIRST_FORK, philo);
	status = pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime('M'));
	philo->meals_counter++;
	write_status(EATING, philo);
	my_usleep(philo->program->t_eat, philo->program);
	if (philo->program->n_meals > 0 && philo->meals_counter == philo->program->n_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	status = pthread_mutex_unlock(&philo->first_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
	status = pthread_mutex_unlock(&philo->second_fork->fork);
	if (status != 0)
		print_error_and_exit("cannot unlock mutex");
}
