/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvutina <alvutina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:15 by alvutina          #+#    #+#             */
/*   Updated: 2024/07/29 11:44:15 by alvutina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* function returns the current time in milliseconds since the Unix epoch.
It uses gettimeofday to get the current time and converts
it into milliseconds.*/
long long	timestart(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
}

/*function returns the number of milliseconds elapsed since the start of
the simulation. It uses gettimeofday to get the current time
and subtracts the start time of the simulation.*/
long long	timestamp(t_dining_simulation *store)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - store->time_start);
}

/*The philo_sleep function makes a philosopher sleep for a specified time,
periodically checking if the time has elapsed while ensuring thread
safety with a mutex.*/
void	philo_sleep(t_philo *philo, int wait)
{
	long long	current_time;
	long long	diff;

	current_time = timestamp(philo->args);
	while (1)
	{
		pthread_mutex_lock(&philo->args->checks);
		diff = (timestamp(philo->args) - current_time);
		if (diff >= wait)
		{
			pthread_mutex_unlock(&philo->args->checks);
			break ;
		}
		pthread_mutex_unlock(&philo->args->checks);
		usleep (100);
	}
}

void	output_fork(t_philo *philo)
{
	output(philo, TFORK);
	output(philo, TFORK);
}

void	output(t_philo *philo, char *str)
{
	if (philo->args->finish_sim == false)
	{
		pthread_mutex_lock(&philo->args->checks);
		printf("%lld %d %s\n", \
		timestamp(philo->args), philo->id_num, str);
		pthread_mutex_unlock(&philo->args->checks);
	}
}
