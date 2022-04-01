/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:34:09 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 14:22:25 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_bonus.h"

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
			return (0);
		philo[i]->id = i;
		philo[i]->args = args;
		sem_unlink("eatcounter");
		philo[i]->sem_eat = sem_open("eatcounter", O_CREAT, 0644, 1);
		if (philo[i]->sem_eat == SEM_FAILED)
			return (NULL);
		i++;
	}
	return (philo);
}

int	sems_init(t_args *args)
{
	sem_unlink("forking");
	args->sem_forks = sem_open("forking", O_CREAT, 0644,
			args->philo_amount);
	if (args->sem_forks == SEM_FAILED)
		return (1);
	sem_unlink("writing");
	args->sem_write = sem_open("writing", O_CREAT, 0644, 1);
	if (args->sem_write == SEM_FAILED)
		return (1);
	sem_unlink("meal");
	args->sem_meal = sem_open("meal", O_CREAT, 0644, 1);
	if (args->sem_meal == SEM_FAILED)
		return (1);
	return (0);
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
	if (sems_init(args))
		return (NULL);
	args->start_time = get_time();
	args->philo = philo_init(args);
	return (args);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->args->sem_forks);
	message(philo->args, philo->id, "has taken the left fork");
	sem_wait(philo->args->sem_forks);
	message(philo->args, philo->id, "has taken the right fork");
	message(philo->args, philo->id, "is eating");
	sem_wait(philo->sem_eat);
	sem_post(philo->args->sem_meal);
	philo->last_meal_time = get_time();
	usleep(philo->args->time_to_eat * 1000);
	sem_post(philo->sem_eat);
}
