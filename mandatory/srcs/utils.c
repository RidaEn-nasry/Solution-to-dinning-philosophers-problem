/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:32:33 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/01 14:19:28 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	message(t_args *table, int philo_number, char *msg)
{
	pthread_mutex_lock(&table->mutex_write);
	printf("[%d]\tPhilosopher %d %s\n", get_time() - table->start_time,
		philo_number + 1, msg);
	if (msg[0] != 'd')
		pthread_mutex_unlock(&table->mutex_write);
}

int	is_num(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] < '0' || string[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	convert(const char *str)
{
	int					sign;
	long long			result;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' \
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
				sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
			result *= 10;
			result += str[i++] - '0';
	}
		result *= sign;
	if (result > INT_MAX || result < INT_MIN)
		return (0);
	return (result);
}
