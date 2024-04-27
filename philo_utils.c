/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:10:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/27 17:21:37 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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
	if (x > 2147483648 || (x * s) <= 0)
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
