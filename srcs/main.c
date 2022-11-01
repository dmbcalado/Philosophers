/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:42:59 by dmendonc          #+#    #+#             */
/*   Updated: 2022/10/31 18:32:56 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	creating_philos(t_philo *info)
{
	int	i;
	int	deaths;

	i = -1;
	deaths = 0;
	info->deaths = 0;
	info->philos = (t_individual *)malloc(info->nbr_of_p * \
	sizeof(t_individual));
	if (!info->philos)
		exit_fail(8);
	while (++i < info->nbr_of_p)
		starting_philo_data(info, i);
	initialization_mutexs(info);
	i = -1;
	while (++i < info->nbr_of_p)
	{
		pthread_create(&info->philos[i].philo, NULL, &routine, \
		&info->philos[i]);
	}
	while (deaths < info->nbr_of_p)
	{
		pthread_mutex_lock(&info->mutexend);
		deaths = info->deaths;
		pthread_mutex_unlock(&info->mutexend);
	}
}

//....................................................................

void	destroying_philos(t_philo *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_p)
	{
		if (pthread_join(info->philos[i].philo, NULL) != 0)
			exit_fail(5);
	}
	i = -1;
	while (++i < info->nbr_of_p)
		pthread_mutex_destroy(&info->mutexfork[i]);
	pthread_mutex_destroy(&info->mutexend);
	pthread_mutex_destroy(&info->mutexstart);
	pthread_mutex_destroy(&info->mutexprint);
	free(info->mutexfork);
	free(info->philos);
}

//....................................................................

int	main(int argc, char **argv)
{
	t_philo	info;

	if (argc > 1 && argc < 7)
	{
		colect_all_info(argc, argv, &info);
		creating_philos(&info);
		destroying_philos(&info);
	}
	else
		exit_fail(1);
}
