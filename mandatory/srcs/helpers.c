/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:32:48 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 14:19:04 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	invalid(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong argument number\n");
		return (1);
	}
	while (i < argc)
	{
		if (argv[i][0] == '-' || !is_num(argv[i])
			|| !convert(argv[i]))
		{
			printf("Error: Invalid Arguments.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

t_philo	**philo_init(t_args *args)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * args->philo_amount);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < args->philo_amount)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		if (pthread_mutex_init(&philo[i]->mutex_eating, NULL))
			return (NULL);
		philo[i]->philo_number = i;
		philo[i]->args = args;
		philo[i]->is_eating = 0;
		philo[i]->meal_counter = 0;
		philo[i]->philo_left_fork = i;
		philo[i]->philo_right_fork = (i + 1) % args->philo_amount;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*fork_init(t_args	*args)
{
	pthread_mutex_t	*mutex_forks;
	int				i;

	i = 0;
	mutex_forks = malloc(sizeof(pthread_mutex_t) * args->philo_amount);
	if (!mutex_forks)
		return (NULL);
	while (i < args->philo_amount)
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		i++;
	}
	return (mutex_forks);
}

t_args	*init(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->philo_amount = convert(argv[1]);
	args->time_to_die = convert(argv[2]);
	args->time_to_eat = convert(argv[3]);
	args->time_to_sleep = convert(argv[4]);
	args->meal_ammount = 0;
	if (argc == 6)
		args->meal_ammount = convert(argv[5]);
	pthread_mutex_init(&args->mutex_write, NULL);
	args->start_time = get_time();
	args->mutex_forks = fork_init(args);
	args->philo = philo_init(args);
	if (!args->philo || !args->mutex_forks)
		return (NULL);
	return (args);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_forks[philo->philo_left_fork]);
	message(philo->args, philo->philo_number, "has taken the left fork");
	pthread_mutex_lock(&philo->args->mutex_forks[philo->philo_right_fork]);
	message(philo->args, philo->philo_number, "has taken the right fork");
	pthread_mutex_lock(&philo->mutex_eating);
	philo->last_meal_time = get_time();
	philo->is_eating = 1;
	message(philo->args, philo->philo_number, "is eating");
	usleep(philo->args->time_to_eat * 1000);
	philo->is_eating = 0;
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->mutex_eating);
}
