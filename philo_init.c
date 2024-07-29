/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvutina <alvutina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:26:15 by alvutina          #+#    #+#             */
/*   Updated: 2024/07/29 11:26:15 by alvutina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s\n", ERROR2);
		printf("%s\n", ERROR3);
		return (1); 
	}
	if (argc == 6)
	{
		if (argv[5][0] == '\0') 
		{
			printf("%s", ERROR1);
			return (1);
		}
	}
	if (check_digit(argv))
	{
		printf("%s", ERROR1);
		return (1);
	}
	return (0);
}

int	check_error(t_dining_simulation *store, char **argv)
{
	if (store->time_sleep < 0 || store->time_eat < 0 || store->time_die < 0
		|| store->num_philo < 0)
		return (1);
	if (argv[5])
	{
		store->meal_limit = ft_atoi(argv[5]);
		if (store->meal_limit < 0)
			return (1);
	}
	else
		store->meal_limit = false;
	return (0);
}

int	initialization(char **argv, t_dining_simulation *store)
{
	int	i;

	i = -1;
	store->error = false;
	store->finish_game = false;
	store->end_meal = 0;
	store->num_philo = ft_atoi(argv[1]);
	store->time_die = ft_atoi(argv[2]);
	store->time_eat = ft_atoi(argv[3]);
	store->time_sleep = ft_atoi(argv[4]);
	if (check_error(store, argv)) 
	{
		printf("%s", ERROR1);
		return (free(store), 1);
	}
	store->philo = ft_calloc(store->num_philo, (sizeof(t_philo)));
	store->fork = ft_calloc(store->num_philo, (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&store->checks, NULL);
	while (++i < store->num_philo)
		pthread_mutex_init(&store->fork[i], NULL);
	init_philosophers(store);
	store->time_start = timestart();
	return (0);
}

void	init_philosophers(t_dining_simulation *store)
{
	int	i;

	i = 0;
	while (i < store->num_philo)
	{
		store->philo[i].id_num = i + 1;
		store->philo[i].meal_eaten = 0;
		store->philo[i].last_meal = 0;
		store->philo[i].left_fork = i;
		store->philo[i].right_fork = (i + 1) % store->num_philo;
		store->philo[i].args = store; 
		i++;
	}
}

void	philo_destroy(t_dining_simulation *store)
{
	int	i;

	i = 0;
	if (store->num_philo > 1)
	{
		while (i < store->num_philo)
			pthread_join(store->philo[i++].thread, NULL);
	}
	i = 0;
	while (i < store->num_philo)
		pthread_mutex_destroy(&store->fork[i++]);
	pthread_mutex_destroy(&store->checks);
	free(store->philo);
	free(store->fork);
	free(store);
}
