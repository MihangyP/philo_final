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
		precise_usleep(philo->program->time_to_sleep, philo->program);
		thinking(philo, false);
	}
	return (NULL);
}


void	*monitor_dinner(void *data)
{
	t_program	*program;
	int		i;

	program = (t_program *)data;
	while (!all_threads_running(&program->program_mutex, &program->threads_running_nbr, program->philo_nbr))
		;
	while (!simulation_finished(program))
	{
		i = -1;
		while (++i < program->philo_nbr && !simulation_finished(program))
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

void	dinner_start(t_program *program)
{
	int	i;

	i = -1;
	if (program->nbr_limit_meals == 0)
		return ;
	else if (program->philo_nbr == 1)
		safe_thread_handle(&program->philos[0].thread_id, lone_philo, &program->philos[0], CREATE);
	else
	{
		while (++i < program->philo_nbr)
			safe_thread_handle(&program->philos[i].thread_id, dinner_simulation, &program->philos[i], CREATE);
	}
	safe_thread_handle(&program->monitor, monitor_dinner, program, CREATE);
	program->start_simulation = gettime('M');
	set_bool(&program->program_mutex, &program->all_threads_ready, true);
	i = -1;
	while (++i < program->philo_nbr)
		safe_thread_handle(&program->philos[i].thread_id, NULL, NULL, JOIN);

	set_bool(&program->program_mutex, &program->end_simulation, true);
	safe_thread_handle(&program->monitor, NULL, NULL, JOIN);
}
