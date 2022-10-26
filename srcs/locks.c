/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:11:46 by dmendonc          #+#    #+#             */
/*   Updated: 2022/10/26 20:45:27 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// ------		Checks and Locks if the forks are available.   	-------

int	lock_forks(t_individual *indiv, t_philo *info)
{
	if (indiv->id < info->nbr_of_p)
	{
		pthread_mutex_lock(indiv->mutexfork_l);
		pthread_mutex_lock(indiv->mutexfork_r);
		get_time(indiv);
		if (checker_inside_locks(indiv, info) == 1)
			return (1);
		pthread_mutex_lock(&indiv->data->mutexprint);
		printf("%d %d is eating.\n", indiv->timers.time_ran, indiv->id);
		pthread_mutex_unlock(&indiv->data->mutexprint);
	}
	else
	{
		pthread_mutex_lock(indiv->mutexfork_l);
		pthread_mutex_lock(indiv->mutexfork_r);
		get_time(indiv);
		pthread_mutex_lock(&indiv->data->mutexprint);
		printf("%d %d is eating.\n", indiv->timers.time_ran, indiv->id);
		pthread_mutex_unlock(&indiv->data->mutexprint);
	}
	return (0);
}

void	unlock_forks(t_individual *indiv, t_philo *info)
{
	if (indiv->id < info->nbr_of_p)
	{
		pthread_mutex_unlock(indiv->mutexfork_l);
		pthread_mutex_unlock(indiv->mutexfork_r);
	}
	else
	{
		pthread_mutex_unlock(indiv->mutexfork_l);
		pthread_mutex_unlock(indiv->mutexfork_r);
	}
}