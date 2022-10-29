/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:51:39 by dmendonc          #+#    #+#             */
/*   Updated: 2022/10/28 23:58:53 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

// ------- Struct that carrys all the individual timers --------
typedef struct s_philo		t_philo;
typedef struct s_individual	t_individual;

typedef struct s_timing
{
	int				gap;
	int				flag;
	int				time_ran;
	long int		t;
	long int		time_start;
	long int		time_freeze;
	long int		time_eating;
	long int		time_thinking;
	long int		time_sleeping;
	struct timeval	time;
}				t_timing;

// ------		->
// INFO

struct	s_philo
{
	int				start;
	int				flag;
	int				deaths;
	int				*forks;
	int				nbr_of_p;
	int				time_die;
	int				time_eat;
	int				time_think;
	int				time_sleep;
	int				eating_max;
	long int		time_start;
	t_individual	*philos;
	pthread_mutex_t	*mutexfork;
	pthread_mutex_t	mutexend;
	pthread_mutex_t	mutexprint;
	pthread_mutex_t	mutexstart;
};

// ------ Struct that carrys the information of the thread ------
// INDIV

struct	s_individual
{
	int				nbr_p;
	int				id;
	int				max_eat;
	int				counter;
	int				time_eat;
	int				eat_return;
	int				time_death;
	int				time_sleep;
	int				times_eaten;
	t_philo			*data;
	t_timing		timers;
	pthread_t		philo;
	pthread_mutex_t	*mutexstart;
	pthread_mutex_t	*mutexprint;
	pthread_mutex_t	*mutexfork_r;
	pthread_mutex_t	*mutexfork_l;
};

// Starting functions

int		colect_nbr(char **argv, int ind);
void	starting_time(t_individual *indiv);
void	colect_all_info(int argc, char **argv, t_philo *info);

// Timer functions and safetys

int		timer(void);
void	get_time(t_individual *indiv);
void	reset_timer(t_individual *indiv, t_philo *info);

// Checkers & Fails

void	exit_fail(int fail);
int		checker(t_individual *indiv, t_philo *info);
int		checker_inside_locks(t_individual *indiv, t_philo *info);
int		check_forks(t_individual *indiv, t_philo *info);
void	print_death(t_individual *indiv, t_philo *info);

// Locking and Unlocking the mutexs.

int		lock_forks(t_individual *indiv, t_philo *info);
void	unlock_forks(t_individual *indiv, t_philo *info);
void	initialization_mutexs(t_philo *info);

// Start&End functions for the threads. and the forks lists.

void	creating_philos(t_philo *info);
void	creating_daforks(t_philo *info);
void	starting_synced(t_individual *indiv);
void	starting_philo_data(t_philo *info, int i);
void	ending_philos(t_philo *info);
void	ending_dead_philo(t_individual *indiv, t_philo *info);

// Running the treads.

void	*routine(void *ptr);
void	routina(t_individual *indiv, t_philo *info);
void	engine(t_individual *indiv, t_philo *info);
int		eating(t_individual *indiv, t_philo *info);
int		sleeping(t_individual *indiv, t_philo *info);
int		thinking(t_individual *indiv, t_philo *info);

#endif