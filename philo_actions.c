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

/*function simulates the behavior of a single philosopher.
It locks their left fork, sleeps for the duration of time_die, then unlocks
the fork and marks the philosopher as dead. It also sets the finish_sim flag
to true to end the simulation.*/
void	*one_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->args->fork[philo->left_fork]);
	output(philo, TFORK);
	philo_sleep(philo, philo->args->time_die); 
	pthread_mutex_unlock(&philo->args->fork[philo->left_fork]);
	output(philo, DIED);
	pthread_mutex_lock(&philo->args->checks);
	philo->args->finish_sim = true;
	pthread_mutex_unlock(&philo->args->checks);
	return (NULL);
}

/*function handles a philosopher's attempt to pick up both forks.
Depending on the philosopher's ID, it either locks the left fork
first or the right fork first, ensuring that forks are acquired
in a way that avoids deadlock.*/
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

/*function handles the philosopher eating:
it acquires forks, updates meal time and count,
and releases forks afterward.*/
void	eating(t_philo *philo)
{
	bool	lock;

	lock = true;
	pthread_mutex_lock(&philo->args->checks);
	if (philo->args->finish_sim == false)
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

/*The `thinking` function outputs a message indicating that
the philosopher is thinking, provided that the simulation is not finished.*/
void	thinking(t_philo *philo)
{
	if (philo->args->finish_sim == false)
		output(philo, THINKING);
}

/* function outputs a message indicating that the philosopher is sleeping
and then puts the philosopher to sleep if the simulation is not finished.*/
void	going_sleep(t_philo *philo)
{
	if (philo->args->finish_sim == false)
	{
		output(philo, SLEEPING);
		philo_sleep(philo, philo->args->time_sleep);
	}
}
