/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:30 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:32 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_init(t_program *program)
{
	int		i;
	int		state;
	t_philo	*philo;

	i = -1;
	while (++i < program->n_philo)
	{
		philo = program->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->program = program;
		state = pthread_mutex_init(&philo->philo_mutex, NULL);
		if (state != 0)
			print_error_and_exit("cannot init mutex");
		philo->first_fork = &program->forks[(i + 1) % program->n_philo];
		philo->second_fork = &program->forks[i];
		if (philo->id % 2 == 0)
		{
			philo->first_fork = &program->forks[i];
			philo->second_fork = &program->forks[(i + 1) % program->n_philo];
		}
	}
}

void	init_forks(t_program *program)
{
	int	i;
	int	status;

	i = -1;
	while (++i < program->n_philo)
	{
		status = pthread_mutex_init(&program->forks[i].fork, NULL);
		if (status != 0)
			print_error_and_exit("cannot init mutex");
		program->forks[i].fork_id = i;
	}
}

void	data_init(t_program *program)
{
	int	status;

	program->end_simulation = false;
	program->all_threads_ready = false;
	program->threads_running_nbr = 0;
	program->philos = malloc(program->n_philo * sizeof(t_philo));
	if (program->philos == NULL)
		print_error_and_exit("malloc error");
	status = pthread_mutex_init(&program->program_mutex, NULL);
	if (status != 0)
		print_error_and_exit("cannot init mutex");
	status = pthread_mutex_init(&program->write_mutex, NULL);
	if (status != 0)
		print_error_and_exit("cannot init mutex");
	program->forks = malloc(program->n_philo * sizeof(t_fork));
	if (program->forks == NULL)
		print_error_and_exit("malloc error");
	init_forks(program);
	philo_init(program);
}
