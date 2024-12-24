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

	i = -1;
	while (++i < program->philo_nbr)
	{
		philo = program->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&program->write_mutex, DESTROY);
	safe_mutex_handle(&program->program_mutex, DESTROY);
	free(program->forks);
	free(program->philos);
}
