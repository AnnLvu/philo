/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvutina <alvutina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:06:10 by alvutina          #+#    #+#             */
/*   Updated: 2024/07/29 10:06:10 by alvutina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

/*------------------------------ LIBRARIES ------------------------------*/

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h> 
# include <sys/time.h>
# include <limits.h> 

/*------------------------ PRINT TO STDOUT -------------------------*/

# define ERROR1			"Invalid argument detected"
# define ERROR2			"The program expects 4-5 args:" 
# define ERROR3			"Ex.: ./philo [num of philo] [time die] [time eat]..."
# define TFORK			"has taken a fork"
# define DIED			" died"
# define EATING			"is eating"
# define THINKING		"is thinking"
# define SLEEPING		"is sleeping" 

/*---------------------------- STRUCTURES ----------------------------*/

typedef struct s_philo				t_philo;
typedef struct s_dining_simulation	t_dining_simulation;

typedef struct s_philo
{
	int							meal_eaten;
	int							id_num;
	pthread_t					thread;
	long long					last_meal;
	int							right_fork;
	int							left_fork;
	t_dining_simulation			*args;
}	t_philo; 

typedef struct s_dining_simulation
{
	int				error;
	bool			finish_sim;
	int				end_meal;
	long long		time_start;
	long long		time_eat;
	long long		time_die;
	long long		time_sleep;
	int				num_philo;
	int				meal_limit;
	t_philo			*philo;
	pthread_mutex_t	checks;
	pthread_mutex_t	*fork;
}	t_dining_simulation;

/*--------------------------- FUNCTIONS ---------------------------*/

int			check_digit(char **str);
int			ft_atoi(const char *str);
int			check_args(int argc, char **argv);
int			check_error(t_dining_simulation *store, char **argv);
long long	timestart(void);
long long	timestamp(t_dining_simulation *store);
int			initialization(char **argv, t_dining_simulation *store);
void		*ft_calloc(size_t count, size_t size);
void		init_philosophers(t_dining_simulation *store);
void		philo_start(t_dining_simulation *store);
void		*life_cycle(void *val);
void		*one_philo(void *p);
void		output(t_philo *philo, char *str);
void		philo_sleep(t_philo *philo, int wait);
void		philo_destroy(t_dining_simulation *store);
void		check_philo_status(t_dining_simulation *store);
void		eating(t_philo *philo);
void		thinking(t_philo *philo);
void		going_sleep(t_philo *philo);
void		check_life(t_philo *philo);
void		taken_fork(t_philo *philo);
void		meal_limit_check(t_dining_simulation *store);
void		output_fork(t_philo *philo);

#endif