/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:01:39 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/24 08:28:35 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	PROTOCOL OUTLINES
	1) HEADER
	- MESSAGE SIZE, in chars, sizeof(int) (24 bits)
	- CONTINUE in next batch, 1 bit
	- PARITY, 1 bit
	2) MESSAGE
	- RESEND FLAG, 1 bit
	- DATA, 8 bits
	- PARITY, 1 bit
*/

/*
	TRANSMIT STATE, enum
	INIT -1,
	RESEND FLAG 0,
	DATA 1,
	PARITY FLAG 2.

	stage = ++stage % 3
*/

/*
	Allowed stuff:
	- write
	- ft_printf
	- signal
	- sigemptyset
	- sigaddset
	- sigaction
	- kill
	- getpid
	- malloc
	- free
	- pause
	- sleep
	- usleep
	- exit
*/

#include "server.h"

volatile t_signal	g_signal_data;

void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	g_signal_data.sigusr_number = 1;
	g_signal_data.arrived = 1;
	g_signal_data.response_target_pid = info->si_pid;
	return ;
}

void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	g_signal_data.sigusr_number = 2;
	g_signal_data.arrived = 1;
	g_signal_data.response_target_pid = info->si_pid;
	return ;
}

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	printf("Minitalk Server PID: %d\n", getpid());
	if (init_signal_handlers(&sa1, &sa2) != 0)
	{
		return (1);
	}
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	while (1)
	{
		if (g_signal_data.arrived == 1)
		{
			g_signal_data.arrived = 0;
			printf("sig %i from PID %d\n", g_signal_data.sigusr_number, (int)g_signal_data.response_target_pid);
		}
		pause();
	}
	return (0);
}

int	init_signal_handlers(struct sigaction *sa1, struct sigaction *sa2)
{
	int	errors;

	errors = 0;
	sa1->sa_sigaction = sigusr1_handler;
	errors += sigemptyset(&sa1->sa_mask);
	errors += sigaddset(&sa1->sa_mask, SIGUSR1);
	errors += sigaddset(&sa1->sa_mask, SIGUSR2);
	sa1->sa_flags = SA_SIGINFO;
	sa2->sa_sigaction = sigusr2_handler;
	errors += sigemptyset(&sa1->sa_mask);
	errors += sigaddset(&sa2->sa_mask, SIGUSR1);
	errors += sigaddset(&sa2->sa_mask, SIGUSR2);
	sa2->sa_flags = SA_SIGINFO;
	return (errors);
}
