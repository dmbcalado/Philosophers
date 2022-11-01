/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:11:46 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/01 14:39:33 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// ------		Checks and Locks if the forks are available.   	-------

int	lock_forks(t_individual *indiv, t_philo *info)
{
	if (indiv->id < info->nbr_of_p && indiv->mutexfork_l)
	{
		pthread_mutex_lock(indiv->mutexfork_l);
		pthread_mutex_lock(indiv->mutexfork_r);
		get_time(indiv);
		if (checker_inside_locks(indiv, info) == 1)
			return (1);
		print_eating(indiv);
	}
	else if (indiv->mutexfork_l)
	{
		pthread_mutex_lock(indiv->mutexfork_l);
		pthread_mutex_lock(indiv->mutexfork_r);
		get_time(indiv);
		if (checker_inside_locks(indiv, info) == 1)
			return (1);
		print_eating(indiv);
	}
	return (0);
}

void	unlock_forks(t_individual *indiv)
{
	if (indiv->mutexfork_l)
	{
		pthread_mutex_unlock(indiv->mutexfork_l);
		pthread_mutex_unlock(indiv->mutexfork_r);
	}
}

void	print_eating(t_individual *indiv)
{
	if (indiv->flag == 0 && indiv->id % 2 == 1 && indiv->timers.time_ran < 50)
	{
		printf("%d %d has taken a fork\n%d %d has taken a fork\n", \
		0, indiv->id, 0, indiv->id);
		printf("%d %d is eating\n", 0, indiv->id);
		indiv->flag = 1;
	}
	else
	{
		printf("%d %d has taken a fork\n%d %d has taken a fork\n", \
		indiv->timers.time_ran, indiv->id, indiv->timers.time_ran, indiv->id);
		printf("%d %d is eating\n", indiv->timers.time_ran, indiv->id);
	}
}
