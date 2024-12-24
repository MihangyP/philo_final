/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:47:03 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/24 15:47:17 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

enum	e_philo_status
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct	s_program	t_program;

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct	s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread_id;
	t_program			*program;
}	t_philo;

struct	s_program
{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			all_threads_ready;
	long			threads_running_nbr;
	pthread_t		monitor;
	pthread_mutex_t	program_mutex;	
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

void	print_error_and_exit(const char *err_message);
long	ft_atol(char *str);

void	data_init(t_program *program);

void	*safe_malloc(size_t	bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, int opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, int opcode);

void	extract_data(t_program *program, char **av);

void	write_status(int status, t_philo *philo);
long	gettime(char c);
bool	simulation_finished(t_program *program);
void	simulation(t_program *program);

void	set_long(pthread_mutex_t *mutex, long *dest, long value);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
long	get_long(pthread_mutex_t *mutex, long *value);

void	de_synchronise_philos(t_philo *philo);
void	wait_all_threads(t_program *program);
void	increase_long(pthread_mutex_t *mutex, long *value);
void	eat(t_philo *philo);
void	my_usleep(long usec, t_program *program);
void	thinking(t_philo *philo, bool pre_simulation);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
bool	philo_died(t_philo *philo);
void	free_all(t_program *program);

#endif
