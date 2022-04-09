/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:35:03 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 14:17:36 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_philo
{
	pid_t			philo_pid;
	pthread_t		monitor_die;
	int				id;
	int				last_meal_time;
	sem_t			*sem_eat;
	struct s_args	*args;
}				t_philo;

typedef struct s_args
{
	pthread_t		monitor_meal;
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_ammount;
	int				start_time;
	sem_t			*sem_write;
	sem_t			*sem_meal;
	sem_t			*sem_forks;
	t_philo			**philo;
}				t_args;

int			get_time(void);
void		message(t_args *table, int philo_number, char *msg);
t_args		*init(int argc, char **argv);
void		take_fork(t_philo *ph);
void		eat(t_philo *ph);
void		go_to_bed(t_philo *ph);
int			is_num(char *string);
void		ft_usleep(long int time_in_ms);

long long	convert(const char *str);
int			invalid(char **argv, int argc);
void		close_processes(t_args *table);

#endif