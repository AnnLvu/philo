/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvutina <alvutina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:34 by alvutina          #+#    #+#             */
/*   Updated: 2024/07/29 11:44:34 by alvutina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The main function checks command-line arguments, initializes the simulation,
 starts the philosophers, and then cleans up resources.*/
#include "philo.h" 

int	main(int argc, char **argv)
{
	t_dining_simulation	*store;

	if (check_args(argc, argv) != 0)
		return (1);
	store = (t_dining_simulation *)ft_calloc(1, sizeof(t_dining_simulation));
	if (!store)
		return (1);
	if (initialization(argv, store))
		return (1);
	philo_start(store);
	philo_destroy(store);
	return (0);
}
