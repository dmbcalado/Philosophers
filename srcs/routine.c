/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:32:33 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/01 14:26:06 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Routine function, the one called by the pthread_create.
// .......................................................................
// At this point we are working with individual threads, and we 
// want this function to be the heart of the routina function &
// where we lock the deaths.
// .......................................................................

void	*routine(void *ptr)
{
	t_philo			*info;
	t_individual	*indiv;

	indiv = (t_individual *)ptr;
	info = (t_philo *)indiv->data;
	indiv->times_eaten = 0;
	starting_time(indiv);
	if (indiv->nbr_p == 1)
	{
		indiv->timers.time_start = indiv->timers.time_start;
	}
	routina(indiv, info);
	pthread_mutex_lock(&info->mutexend);
	info->deaths++;
	pthread_mutex_unlock(&info->mutexend);
	return (&info->deaths);
}

// Routina function, the one who runs the philos tasks.
//.......................................................................
// This function will run till one of the philosofers die, 
// atributing each tasks and checking if times_eaten hasnt 
// been reach.
//.......................................................................

void	routina(t_individual *indiv, t_philo *info)
{
	while (1)
	{
		if (eating(indiv, info) == 0)
		{
			if (sleeping(indiv, info) == 1)
				break ;
		}
		else
			break ;
	}
}

// Function that performs the task of eating.
//..............................................................
// Eating is basically locking the mutexfork s, restoring the 
// philosophers time till dying to the maximum value, wich 
// is the one the user gave has a parameter, and make the 
// philosofer run the time_eat with the forks locked.
//.............................................................

int	eating(t_individual *indiv, t_philo *info)
{
	if (lock_forks(indiv, info) == 1)
		return (1);
	get_time(indiv);
	indiv->timers.time_eating = 0;
	if (indiv->nbr_p > 1)
		indiv->timers.time_start = indiv->timers.t;
	while (indiv->timers.time_eating < indiv->time_eat)
	{
		if (checker_inside_locks(indiv, info) == 1)
			return (1);
		get_time(indiv);
		indiv->timers.time_eating = indiv->timers.t - indiv->timers.time_start;
	}
	indiv->times_eaten++;
	while (indiv->timers.time_ran < indiv->timers.time_eating)
		get_time(indiv);
	if (checker_inside_locks(indiv, info) == 1)
		return (1);
	printf("%d %d is sleeping\n", indiv->timers.time_ran, indiv->id);
	unlock_forks(indiv);
	if (checker(indiv, info) == 1)
		return (1);
	return (0);
}

// Function that performs the task of sleeping and thinking.
//..............................................................
// Thinking is actually a "ill try to lock the mutexforks now",
// and since the pthread_mutex_lock will wait till he can lock 
// the forks, we just need to after sleeping print that he is
// thinking.
//..............................................................

int	sleeping(t_individual *indiv, t_philo *info)
{
	indiv->timers.time_sleeping = 0;
	indiv->timers.time_freeze = indiv->timers.t;
	get_time(indiv);
	if (checker(indiv, info) == 1)
		return (1);
	while (indiv->timers.time_sleeping < indiv->time_sleep)
	{
		if (checker(indiv, info) == 1)
			return (1);
		get_time(indiv);
		indiv->timers.time_sleeping = indiv->timers.t - \
		indiv->timers.time_freeze;
	}
	while (indiv->timers.time_ran < indiv->timers.time_eating)
		get_time(indiv);
	if (checker(indiv, info) == 1)
		return (1);
	printf("%d %d is thinking\n", indiv->timers.time_ran, indiv->id);
	indiv->timers.time_sleeping = 0;
	return (0);
}
