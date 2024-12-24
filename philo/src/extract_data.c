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
	program->n_philo = ft_atol(av[1]);
	program->t_die = ft_atol(av[2]) * 1000;
	program->t_eat = ft_atol(av[3]) * 1000;
	program->t_sleep = ft_atol(av[4]) * 1000;
	if (program->t_die < 60 * 1000 ||
		program->t_eat < 60 * 1000 ||
		program->t_sleep < 60 * 1000)
		print_error_and_exit("timestamp should be > than 60ms");
	program->n_meals = -69;
	if (av[5])
		program->n_meals = ft_atol(av[5]);
}
