/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fails_and_checkers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:29:17 by dmendonc          #+#    #+#             */
/*   Updated: 2022/10/26 20:52:27 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// ----- Checks if any condition to kill the philosopher is met.  ------

int	checker(t_individual *indiv, t_philo *info)
{
	int	ret;

	get_time(indiv);
	pthread_mutex_lock(&info->mutexend);
	ret = info->deaths;
	pthread_mutex_unlock(&info->mutexend);
	if (ret > 0)
		return (1);
	if (indiv->timers.gap > indiv->time_death)
		print_death(indiv, info);
	else if (indiv->times_eaten >= indiv->data->eating_max)
		return (1);
	return (0);
}

// Checks if any condition to kill the philosopher is met 
// and unlocks the mutex.

int	checker_inside_locks(t_individual *indiv, t_philo *info)
{
	int	ret;

	get_time(indiv);
	pthread_mutex_lock(&info->mutexend);
	ret = info->deaths;
	pthread_mutex_unlock(&info->mutexend);
	if (ret > 0)
	{
		unlock_forks(indiv, info);
		return (1);
	}
	if (indiv->timers.gap > indiv->time_death)
	{
		unlock_forks(indiv, info);
		print_death(indiv, info);
		return (1);
	}
	else if (indiv->times_eaten >= indiv->max_eat)
		return (1);
	return (0);
}

// ----- Checker for any fail running the code. ----- 

void	exit_fail(int fail)
{
	if (fail == 1)
		printf("Invalid arguments.\n");
	if (fail == 2)
		printf("Please enter a positive number of philosophers. \
		\nEnding execution.");
	if (fail == 3)
		printf("Error in memory allocation.\nEnding execution.");
	if (fail == 4)
		printf("Error in the thread creation.\nEnding execution.");
	if (fail == 5)
		printf("Error in joining the threads.\nEnding execution.");
	if (fail == 6)
		printf("Error in unlocking the mutex.\nEnding execution.\n");
	if (fail == 7)
		printf("Error in unlocking the mutex.\nEnding execution.\n");
}

void	print_death(t_individual *indiv, t_philo *info)
{
	int	local;

	pthread_mutex_lock(&info->mutexend);
	local = info->deaths;
	pthread_mutex_unlock(&info->mutexend);
	if (local == 0)
	{
		pthread_mutex_lock(&info->mutexend);
		info->deaths++;
		pthread_mutex_unlock(&info->mutexend);
		if (local == 0)
		{
			pthread_mutex_lock(&indiv->data->mutexprint);
			printf("%d %d died\n", indiv->timers.time_ran, \
			indiv->id);
			pthread_mutex_unlock(&indiv->data->mutexprint);
		}
	}
}
