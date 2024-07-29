/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvutina <alvutina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:27 by alvutina          #+#    #+#             */
/*   Updated: 2024/07/29 11:44:27 by alvutina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->args->fork[philo->left_fork]);
	output(philo, GFORK);
	philo_sleep(philo, philo->args->time_die); 
	pthread_mutex_unlock(&philo->args->fork[philo->left_fork]);
	output(philo, DIED);
	pthread_mutex_lock(&philo->args->checks);
	philo->args->finish_game = true;
	pthread_mutex_unlock(&philo->args->checks);
	return (NULL);
}

void	taken_fork(t_philo *philo)
{
	if (philo->id_num % 2)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->args->fork[philo->left_fork]);
		pthread_mutex_lock(&philo->args->fork[philo->right_fork]);
		output_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->args->fork[philo->right_fork]);
		pthread_mutex_lock(&philo->args->fork[philo->left_fork]);
		output_fork(philo);
	}
}

void	eating(t_philo *philo)
{
	bool	lock;

	lock = true;
	pthread_mutex_lock(&philo->args->checks);
	if (philo->args->finish_game == false)
	{
		lock = false;
		pthread_mutex_unlock(&philo->args->checks);
		taken_fork(philo);
		output(philo, EATING);
		pthread_mutex_lock(&philo->args->checks);
		philo->last_meal = timestamp(philo->args);
		philo->meal_eaten++;
		pthread_mutex_unlock(&philo->args->checks);
		philo_sleep(philo, philo->args->time_eat);
		pthread_mutex_unlock(&philo->args->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->args->fork[philo->right_fork]);
	}
	if (lock)
		pthread_mutex_unlock(&philo->args->checks);
}

void	thinking(t_philo *philo)
{
	if (philo->args->finish_game == false)
		output(philo, THINKING);
}

void	going_sleep(t_philo *philo)
{
	if (philo->args->finish_game == false)
	{
		output(philo, SLEEPING);
		philo_sleep(philo, philo->args->time_sleep);
	}
}
