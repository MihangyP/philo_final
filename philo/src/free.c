/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:58:09 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:10 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_all(t_program *program)
{
	t_philo	*philo;
	int		i;
	int		status;

	i = -1;
	while (++i < program->n_philo)
	{
		philo = program->philos + i;
		status = pthread_mutex_destroy(&philo->philo_mutex);
		if (status != 0)
			print_error_and_exit("cannot destroy mutex");
	}
	status = pthread_mutex_destroy(&program->write_mutex);
	if (status != 0)
		print_error_and_exit("cannot destroy mutex");
	status = pthread_mutex_destroy(&program->program_mutex);
	if (status != 0)
		print_error_and_exit("cannot destroy mutex");
	free(program->forks);
	free(program->philos);
}
