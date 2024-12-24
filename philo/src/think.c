/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:58:25 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:26 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	write_status(THINKING, philo);
	if (philo->program->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->program->time_to_eat;
	t_sleep = philo->program->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->program);
}
