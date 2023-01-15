/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelhadj <abelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:20:10 by abelhadj          #+#    #+#             */
/*   Updated: 2022/12/29 13:44:21 by abelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	long long	i;
	long long	res;
	int			signe;
	long long	n;

	i = 0;
	n = 0;
	res = 0;
	signe = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = res;
		res = res * 10 + str[i++] - 48;
		if (n != res / 10)
			return (-(signe > 0));
	}
	return (res * signe);
}

void	printmsg(int signal)
{
	(void)signal;
	write(1, "✔️✔️ Delivered ✔️✔️\n", 36);
}

void	ft_binconvert(char *msg, pid_t pid)
{
	int	shift;
	int	i;

	i = 0;
	while (1)
	{
		shift = -1;
		while (++shift < 8)
		{
			if (msg[i] & (128 >> shift))
			{
				if (kill(pid, SIGUSR2) < 0)
					exit(1);
			}
			else
			{
				if (kill(pid, SIGUSR1) < 0)
					exit(1);
			}
			usleep(500);
		}
		if (!msg[i])
			break ;
	i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
	{
		ft_putstr("Please write two arg.\n");
		exit(1);
	}
	i = 0;
	while (av[1][i])
	{
		if (!(av[1][i] >= '0' && av[1][i++] <= '9'))
		{
			ft_putstr("Wrong PID.\n");
			exit(1);
		}
	}
	signal(SIGUSR1, printmsg);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_putstr("Negative pid\n");
		exit(1);
	}
	ft_binconvert(av[2], pid);
}
