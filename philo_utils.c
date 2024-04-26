/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:10:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/26 13:30:16 by btvildia         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (ft_strcmp(str, "died") == 0)
	{
		philo->data->dead = 1;
		printf("%ld %d %s\n", get_time(philo->data->time), philo->id + 1, str);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	printf("%ld %d %s\n", get_time(philo->data->time), philo->id + 1, str);
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
	if ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		ft_error("Error");
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
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("Malloc error");
	return (ptr);
}
