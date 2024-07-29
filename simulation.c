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
		while (store->finish_game == false)
			check_philo_status(store);
	}
} 
 
void	*life_cycle(void *val)
{
	t_philo	*philo;
	t_dining_simulation	*store;

	philo = (t_philo *)val;
	store = philo->args;
	while (store->finish_game == false)
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

void	check_philo_status(t_dining_simulation *store)
{
	int	death_id;

	death_id = 0;
	while (store->finish_game == false) 
	{
		check_life(&store->philo[death_id]);
		meal_limit_check(store);
		usleep(1000);
		if (death_id == store->num_philo - 1)
			death_id = -1;
		death_id++;
	}
}

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
		philo->args->finish_game = true; 
		pthread_mutex_unlock(&philo->args->checks);
	}
	if (lock)
		pthread_mutex_unlock(&philo->args->checks);
}

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
			store->finish_game = true;
			pthread_mutex_unlock(&store->checks);
		}
	}
}
