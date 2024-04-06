/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:10:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/06 15:01:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	struct timeval	start;
	struct timeval	now;
	int				diff;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		diff = (now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000
				+ start.tv_usec / 1000);
		if (diff >= time)
			break ;
		usleep(100);
	}
}

long	get_time(struct timeval time)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec * 1000 + now.tv_usec / 1000) - (time.tv_sec * 1000
			+ time.tv_usec / 1000);
	return (diff);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_time(philo->data->time), philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	long	i;
	long	x;
	int		s;

	i = 0;
	x = 0;
	s = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_error("Error");
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (x > 2147483648)
		ft_error("Error");
	return (x * s);
}

void	*ft_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("Malloc error");
	return (ptr);
}