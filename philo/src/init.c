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

void assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->program->philo_nbr;

	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

void	philo_init(t_program *program)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < program->philo_nbr)
	{
		philo = program->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->program = program;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, program->forks, i);
	}
}

void	data_init(t_program *program)
{
	int	i;

	i = -1;
	program->end_simulation = false;
	program->all_threads_ready = false;
	program->threads_running_nbr = 0;
	program->philos = safe_malloc(sizeof(t_philo) * program->philo_nbr);
	safe_mutex_handle(&program->program_mutex, INIT);
	safe_mutex_handle(&program->write_mutex, INIT);
	program->forks = safe_malloc(sizeof(t_fork) * program->philo_nbr);
	while (++i < program->philo_nbr)
	{
		safe_mutex_handle(&program->forks[i].fork, INIT);
		program->forks[i].fork_id = i;
	}
	philo_init(program);
}
