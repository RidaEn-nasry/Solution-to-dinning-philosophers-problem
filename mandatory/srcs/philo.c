/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:31:41 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 14:20:33 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	checking_meal(t_philo	*ph)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&ph->mutex_eating);
	while (i < ph->args->philo_amount)
	{
		if (ph->args->philo[i]->meal_counter >= ph->args->meal_ammount)
		{
			if (i == ph->args->philo_amount - 1)
			{
				pthread_mutex_lock(&ph->args->mutex_write);
				ph->args->finish = 0;
				pthread_mutex_unlock(&ph->args->mutex_write);
			}
			i++;
		}
		else
			break ;
	}
	pthread_mutex_unlock(&ph->mutex_eating);
}

void	*monitor(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (ph->args->finish)
	{
		if (!ph->is_eating
			&& get_time() - ph->last_meal_time >= ph->args->time_to_die)
		{
			pthread_mutex_lock(&ph->mutex_eating);
			message(ph->args, ph->philo_number, "died");
			ph->args->finish = 0;
			pthread_mutex_unlock(&ph->mutex_eating);
		}
		if (ph->args->meal_ammount
			&& ph->meal_counter >= ph->args->meal_ammount)
			checking_meal(ph);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (ph->args->finish)
	{
		take_fork(ph);
		pthread_mutex_unlock(&ph->args->mutex_forks[ph->philo_left_fork]);
		pthread_mutex_unlock(&ph->args->mutex_forks[ph->philo_right_fork]);
		message(ph->args, ph->philo_number, "is sleeping");
		usleep(ph->args->time_to_sleep * 1000);
		message(ph->args, ph->philo_number, "is thinking");
	}
	return (NULL);
}

void	start_philo(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		args->philo[i]->last_meal_time = get_time();
		pthread_create(&args->philo[i]->philo_thread, NULL, routine,
			(void *)args->philo[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < args->philo_amount)
	{
		pthread_create(&args->philo[i]->monitor_thread, NULL, monitor,
			(void *)args->philo[i]);
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_args		*args;

	if (invalid(argv, argc))
		return (1);
	args = init(argc, argv);
	if (!args)
		return (1);
	args->finish = 1;
	args->start_time = get_time();
	start_philo(args);
	while (args->finish)
		;
	return (0);
}
