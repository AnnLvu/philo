/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvutina <alvutina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:06:17 by alvutina          #+#    #+#             */
/*   Updated: 2024/07/29 10:06:17 by alvutina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*function starts the simulation by creating philosopher threads
if there is more than one philosopher. If there is only one philosopher,
it directly runs the one_philo function. It then monitors
the simulation status until it is finished.*/
void	philo_start(t_dining_simulation *store)
{
	int	i;

	if (store->num_philo == 1)
		one_philo(store->philo);
	else
	{
		i = -1;
		while (++i < store->num_philo) 
			pthread_create(&store->philo[i].thread, NULL,
				&life_cycle, (void *)&store->philo[i]); 
		while (store->finish_sim == false)
			check_philo_status(store);
	}
}

/*function controls a philosopher's actions(eating, sleeping, thinking)
while checking if the simulation is finished or
if the philosopher has reached the meal limit.*/
void	*life_cycle(void *val)
{
	t_philo				*philo;
	t_dining_simulation	*store;

	philo = (t_philo *)val;
	store = philo->args;
	while (store->finish_sim == false)
	{
		pthread_mutex_lock(&philo->args->checks);
		if (store->meal_limit > 0 && philo->meal_eaten == store->meal_limit)
		{
			pthread_mutex_unlock(&philo->args->checks);
			break ;
		}
		pthread_mutex_unlock(&philo->args->checks);
		eating(philo);
		going_sleep(philo);
		thinking(philo);
	}
	return (NULL);
}

/*The `check_philo_status` function repeatedly checks each philosopher's
status and meal limits until the simulation ends.*/
void	check_philo_status(t_dining_simulation *store)
{
	int	death_id;

	death_id = 0;
	while (store->finish_sim == false) 
	{
		check_life(&store->philo[death_id]);
		meal_limit_check(store);
		usleep(1000);
		if (death_id == store->num_philo - 1)
			death_id = -1;
		death_id++;
	}
}

/*function checks if a philosopher has died based on elapsed time since
their last meal and updates the simulation state if they have.*/
void	check_life(t_philo *philo)
{
	bool	lock;

	lock = true;
	pthread_mutex_lock(&philo->args->checks);
	if ((timestamp(philo->args) - philo->last_meal) >= philo->args->time_die)
	{
		lock = false;
		pthread_mutex_unlock(&philo->args->checks);
		output(philo, DIED);
		pthread_mutex_lock(&philo->args->checks);
		philo->args->finish_sim = true; 
		pthread_mutex_unlock(&philo->args->checks);
	}
	if (lock)
		pthread_mutex_unlock(&philo->args->checks);
}

/*function checks if all philosophers have reached the meal limit
and ends the simulation if they have.*/
void	meal_limit_check(t_dining_simulation *store)
{
	int	meal_nbr;

	meal_nbr = 0;
	if (store->meal_limit > 0)
	{
		while (meal_nbr < store->num_philo)
		{
			pthread_mutex_lock(&store->checks); 
			if (store->philo[meal_nbr].meal_eaten < store->meal_limit)
			{
				pthread_mutex_unlock(&store->checks);
				break ;
			}
			pthread_mutex_unlock(&store->checks);
			meal_nbr++;
		}
		if (meal_nbr == store->num_philo)
		{
			pthread_mutex_lock(&store->checks);
			store->finish_sim = true;
			pthread_mutex_unlock(&store->checks);
		}
	}
}
