/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:58:04 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:05 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_error_and_exit(const char *err_message)
{
	printf("ERROR: %s\n", err_message);
	exit(69);
}