/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:38:46 by dmendonc          #+#    #+#             */
/*   Updated: 2022/10/29 02:49:17 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	starting_time(t_individual *indiv)
{
	gettimeofday(&indiv->timers.time, NULL);
	pthread_mutex_lock(&indiv->data->mutexstart);
	indiv->data->time_start = indiv->timers.time.tv_sec * 1000 + \
	indiv->timers.time.tv_usec / 1000;
	pthread_mutex_unlock(&indiv->data->mutexstart);
	indiv->timers.time_start = indiv->timers.time.tv_sec * 1000 + \
	indiv->timers.time.tv_usec / 1000;
}

void	get_time(t_individual *indiv)
{
	gettimeofday(&indiv->timers.time, NULL);
	indiv->timers.t = indiv->timers.time.tv_sec * 1000 + \
	indiv->timers.time.tv_usec / 1000;
	indiv->timers.gap = indiv->timers.t - indiv->timers.time_start;
	pthread_mutex_lock(&indiv->data->mutexstart);
	indiv->timers.time_ran = indiv->timers.t - indiv->data->time_start;
	pthread_mutex_unlock(&indiv->data->mutexstart);
}
