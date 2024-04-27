/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:03:40 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/27 20:26:06 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_if_philo_id_less_than_philo_id_next(t_philo *philo)
{
	if (philo->id < philo->id_next)
	{
		pthread_mutex_lock(&philo->data->philo[philo->id].fork);
		ft_print(philo, "has taken a fork");
		if (philo->data->time_die <= get_time(philo->data->time)
			- philo->last_meal)
		{
			ft_print(philo, "died");
			pthread_mutex_unlock(&philo->data->philo[philo->id].fork);
			return (1);
		}
		pthread_mutex_lock(&philo->data->philo[philo->id_next].fork);
		return (0);
	}
	pthread_mutex_lock(&philo->data->philo[philo->id_next].fork);
	ft_print(philo, "has taken a fork");
	if (philo->data->time_die <= get_time(philo->data->time) - philo->last_meal)
	{
		ft_print(philo, "died");
		pthread_mutex_unlock(&philo->data->philo[philo->id_next].fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->philo[philo->id].fork);
	return (0);
}

int	for_take_and_eat(t_philo *philo)
{
	t_philo	*philo_next;

	if (philo->data->nb_philo == 1)
		ft_usleep(philo->data->time_die);
	philo_next = &philo->data->philo[philo->id_next];
	if (check_if_philo_id_less_than_philo_id_next(philo) == 1)
		return (1);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->last_meal = get_time(philo->data->time);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->philo[philo->id].fork);
	pthread_mutex_unlock(&philo->data->philo[philo->id_next].fork);
	return (0);
}

void	simulation(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->print);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->print);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print);
		if (for_take_and_eat(philo) == 1)
			break ;
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep);
		ft_print(philo, "is thinking");
		pthread_mutex_lock(&philo->data->ate);
		if (philo->data->nb_food && ++philo->food == philo->data->nb_food)
		{
			pthread_mutex_unlock(&philo->data->ate);
			break ;
		}
		pthread_mutex_unlock(&philo->data->ate);
	}
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		ft_print(philo, "is thinking");
		ft_usleep(1);
	}
	simulation(philo);
	return (NULL);
}
