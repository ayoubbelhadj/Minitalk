/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelhadj <abelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:21:03 by abelhadj          #+#    #+#             */
/*   Updated: 2022/12/29 13:41:27 by abelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

void	ft_signverify(int signal, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	i;
	static int	bits = 0;

	(void)context;
	if (i != info->si_pid)
	{
		i = info->si_pid;
		bits = 0;
		c = 0xFF;
	}
	if (signal == SIGUSR1)
		c ^= 128 >> bits;
	else if (signal == SIGUSR2)
		c |= 128 >> bits;
	bits++;
	if (bits == 8)
	{
		ft_putchar(c);
		if (!c)
			kill (info->si_pid, SIGUSR1);
		bits = 0;
		c = 0xFF;
	}
}

int	main(void)
{
	struct sigaction	action;
	pid_t				pid;

	action.sa_sigaction = &ft_signverify;
	action.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_putstr("PID: ");
	ft_putnbr((int)pid);
	ft_putchar('\n');
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}
