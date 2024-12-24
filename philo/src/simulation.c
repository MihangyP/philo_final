/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:44 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:45 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->program);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime('M'));
	increase_long(&philo->program->program_mutex, &philo->program->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->program))
		usleep(200);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->program);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime('M'));
	increase_long(&philo->program->program_mutex, &philo->program->threads_running_nbr);	
	de_synchronise_philos(philo);
	while (!simulation_finished(philo->program))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		my_usleep(philo->program->t_sleep, philo->program);
		thinking(philo, false);
	}
	return (NULL);
}

void	*monitor_dinner(void *data)
{
	t_program	*program;
	int		i;

	program = (t_program *)data;
	while (!all_threads_running(&program->program_mutex, &program->threads_running_nbr, program->n_philo))
		;
	while (!simulation_finished(program))
	{
		i = -1;
		while (++i < program->n_philo && !simulation_finished(program))
		{
			if (philo_died(program->philos + i))
			{
				set_bool(&program->program_mutex, &program->end_simulation, true);
				write_status(DIED, program->philos + i);
			}
		}
	}
	return (NULL);
}

void	simulation_next(t_program *program)
{
	int	i;
	int	status;

	program->start_simulation = gettime('M');
	set_bool(&program->program_mutex, &program->all_threads_ready, true);
	i = -1;
	while (++i < program->n_philo)
	{
		status = pthread_join(program->philos[i].thread_id, NULL);
		if (status != 0)
			print_error_and_exit("cannot join thread");
	}
	set_bool(&program->program_mutex, &program->end_simulation, true);
	status = pthread_join(program->monitor, NULL);
	if (status != 0)
		print_error_and_exit("cannot join thread");
}

void	simulation(t_program *program)
{
	int	i;
	int	status;

	if (program->n_meals == 0)
		return ;
	else if (program->n_philo == 1)
	{
		status = pthread_create(&program->philos[0].thread_id, NULL, lone_philo, &program->philos[0]);
		if (status != 0)
			print_error_and_exit("cannot create thread");
	}
	else
	{
		i = -1;
		while (++i < program->n_philo)
		{
			status = pthread_create(&program->philos[i].thread_id, NULL, dinner_simulation, &program->philos[i]);
			if (status != 0)
				print_error_and_exit("cannot create thread");
		}
	}
	status = pthread_create(&program->monitor, NULL, monitor_dinner, program);
	if (status != 0)
		print_error_and_exit("cannot create thread");
	simulation_next(program);
}
