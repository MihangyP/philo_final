/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:57:59 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:58:00 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static char *valid_input(char *str)
{
	int	len;
	char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		print_error_and_exit("negative values are forbidden");
	if (!ft_isdigit(*str))
		print_error_and_exit("the input is not a correct digit");
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		print_error_and_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

long	ft_atol(char *str)
{
	long	number;

	number = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		number = (number * 10) + (*str++ - 48);
	if (number > INT_MAX)
		print_error_and_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

long	gettime(char c)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		print_error_and_exit("gettimeofday failed");
	if (c == 'S')
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (c == 'M')
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (c == 'm')
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		print_error_and_exit("Wrong input to gettime !");
	return (6969);
}
