/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:33:22 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 14:20:46 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	pthread_t		monitor_thread;
	int				philo_number;
	int				last_meal_time;
	int				meal_counter;
	int				philo_left_fork;
	int				philo_right_fork;
	int				is_eating;
	pthread_mutex_t	mutex_eating;
	struct s_args	*args;
}				t_philo;

typedef struct s_args
{
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_ammount;
	int				start_time;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	*mutex_forks;
	int				finish;
	t_philo			**philo;
}				t_args;

int			get_time(void);
void		message(t_args *args, int philo_number, char *msg);
t_args		*init(int argc, char **argv);
void		take_fork(t_philo *ph);
void		eat(t_philo *ph);
void		go_to_bed(t_philo *ph);
int			is_num(char *string);
long long	convert(const char *str);
int			invalid(char **argv, int argc);
void		ft_usleep(long int time_in_ms);

#endif