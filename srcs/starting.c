/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:31:39 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/01 14:40:48 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// ------ function that converts the argument to an int -------

int	colect_nbr(char **argv, int ind)
{
	int	i;
	int	nbr;

	i = -1;
	nbr = 0;
	while (argv[ind][++i])
	{
		if (argv[ind][i] > 47 && argv[ind][i] < 57)
			nbr = nbr * 10 + (argv[ind][i] - 48);
		else
			exit_fail(2);
	}
	return (nbr);
}

// ------ 	function that colects all info	 -------

void	colect_all_info(int argc, char **argv, t_philo *info)
{
	info->nbr_of_p = colect_nbr(argv, 1);
	info->time_die = colect_nbr(argv, 2);
	info->time_eat = colect_nbr(argv, 3);
	info->time_sleep = colect_nbr(argv, 4);
	info->deaths = 0;
	if (argc == 6)
		info->eating_max = colect_nbr(argv, 5);
}

// ------	function that atributes the data to the philo. -------

void	starting_philo_data(t_philo *info, int i)
{
	info->philos[i].id = i + 1;
	info->philos[i].time_death = info->time_die;
	info->philos[i].time_eat = info->time_eat;
	info->philos[i].time_sleep = info->time_sleep;
	info->philos[i].max_eat = info->eating_max;
	info->philos[i].data = info;
	info->philos[i].nbr_p = info->nbr_of_p;
	info->philos[i].data->start = 0;
}

// -----	function that initializes the mutexs		---------

void	initialization_mutexs(t_philo *info)
{
	pthread_mutex_init(&info->mutexend, NULL);
	pthread_mutex_init(&info->mutexprint, NULL);
	pthread_mutex_init(&info->mutexstart, NULL);
	info->mutexfork = malloc((info->nbr_of_p) * sizeof(pthread_mutex_t));
	if (!info->mutexfork)
		initilization_fail(info);
	if (info->nbr_of_p > 1)
		initialization_forks(info);
}

void	initialization_forks(t_philo *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_p)
		pthread_mutex_init(&info->mutexfork[i], NULL);
	i = -1;
	while (++i < info->nbr_of_p)
	{
		if (i < info->nbr_of_p - 1)
		{
			info->philos[i].mutexfork_l = &info->mutexfork[i];
			info->philos[i].mutexfork_r = &info->mutexfork[i + 1];
		}
		else
		{
			info->philos[i].mutexfork_l = &info->mutexfork[0];
			info->philos[i].mutexfork_r = &info->mutexfork[info->nbr_of_p - 1];
		}
	}
}
