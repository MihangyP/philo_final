/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:25 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:57:26 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	extract_data(t_program *program, char **av)
{
	program->philo_nbr = ft_atol(av[1]);
	program->time_to_die = ft_atol(av[2]) * 1000;
	program->time_to_eat = ft_atol(av[3]) * 1000;
	program->time_to_sleep = ft_atol(av[4]) * 1000;
	if (program->time_to_die < 6e4 || program->time_to_eat < 6e4 || program->time_to_sleep < 6e4)
		print_error_and_exit("Use timestamp major than 60ms");
	if (av[5])
		program->nbr_limit_meals = ft_atol(av[5]);
	else
		program->nbr_limit_meals = -69;
}
