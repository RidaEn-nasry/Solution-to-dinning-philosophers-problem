/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:34:34 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 12:45 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_bonus.h"

void	*monitor_meal(void *arg)
{
	t_args	*args;
	int		eat_counter;
	int		i;

	eat_counter = 0;
	args = (t_args *)arg;
	while (eat_counter < args->meal_ammount)
	{
		i = 0;
		while (i <= args->philo_amount)
		{
			sem_wait(args->sem_meal);
			i++;
		}
		eat_counter++;
	}
	sem_wait(args->sem_write);
	i = 0;
	while (i < args->philo_amount)
		kill(args->philo[i++]->philo_pid, SIGKILL);
	return (NULL);
}

void	*monitor_die(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (1)
	{
		sem_wait(ph->sem_eat);
		if (get_time() - ph->last_meal_time >= ph->args->time_to_die)
		{
			message(ph->args, ph->id, "died");
			exit(1);
		}
		sem_post(ph->sem_eat);
		ft_usleep(100);
	}
	return (NULL);
}

void	*routine(t_philo	*ph)
{
	while (1)
	{
		take_fork(ph);
		sem_post(ph->args->sem_forks);
		sem_post(ph->args->sem_forks);
		message(ph->args, ph->id, "is sleeping");
		ft_usleep(ph->args->time_to_sleep);
		
		message(ph->args, ph->id, "is thinking");
		ft_usleep(100);
	}
	return (NULL);
}

void	start_philo(t_args	*args)
{
	int	i;

	i = 0;
	if (args->meal_ammount)
		pthread_create(&args->monitor_meal, NULL, monitor_meal,
			(void *)args);
	while (i < args->philo_amount)
	{
		args->philo[i]->philo_pid = fork();
		args->philo[i]->last_meal_time = get_time();
		if (args->philo[i]->philo_pid == 0)
		{
			pthread_create(&args->philo[i]->monitor_die, NULL, monitor_die, \
				(void *)args->philo[i]);
			routine(args->philo[i]);
			exit(1);
		}
		i++;
		ft_usleep(700);
	}
	close_processes(args);
}

int	main(int argc, char **argv)
{
	t_args		*args;

	if (invalid(argv, argc))
		return (1);
	args = init(argc, argv);
	if (!args)
		return (1);
	args->start_time = get_time();
	start_philo(args);
	return (0);
}
