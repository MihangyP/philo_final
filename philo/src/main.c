/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:13 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:15 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	int	state;

	state = pthread_mutex_lock(mutex);
	if (state != 0)
		print_error_and_exit("cannot lock mutex");
	(*value)++;
	state = pthread_mutex_unlock(mutex);
	if (state != 0)
		print_error_and_exit("cannot unlock mutex");
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime('M') - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->program->t_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	run(t_program *program, char **av)
{
	extract_data(program, av);
	data_init(program);
	simulation(program);
}

int main(int ac, char **av)
{
	t_program	program;

	if (ac == 5 || ac == 6)
		run(&program, av);
	else
		print_error_and_exit("Example Usage : ./philo 4 800 300 200 [4]");
	free_all(&program);
	return (0);
}
