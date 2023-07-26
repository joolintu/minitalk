/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:02:50 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/26 03:26:54 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "server.h"


volatile t_signal	g_signal_data;

void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_signal_data.sigusr_bit = 0;
	g_signal_data.arrived = 1;
	g_signal_data.ack_target_pid = info->si_pid;
	(void)sig;
	(void)ucontext;
	return ;
}

void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_signal_data.sigusr_bit = 1;
	g_signal_data.arrived = 1;
	g_signal_data.ack_target_pid = info->si_pid;
	(void)sig;
	(void)ucontext;
	return ;
}

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;
	static t_message	message;

	if (init_signal_handlers(&sa1, &sa2) != 0)
	{
		return (1);
	}
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	init_message(&message);
	printf("Minitalk TEST Server PID: %d\n", getpid()); // TODO: replace with FT-version
	while (1)
	{
		if (g_signal_data.arrived == 1)
		{
			signal_parser(&message);
			g_signal_data.arrived = 0;
			kill(g_signal_data.ack_target_pid, SIGUSR1);
		}
		pause();
	}
	return (0);
}

void	signal_parser(t_message	*message)
{
	//printf("\nSignal Parser: len_counter %u, ", message->len_counter);
	
	if (message->len_counter > 0)
	{
		printf("%i", (int)g_signal_data.sigusr_bit);
		message->msg_len = (message->msg_len << 1) | g_signal_data.sigusr_bit;
		message->len_counter--;

		if (message->len_counter == 0)
		{
			printf("\nReady to allocate msg_string.\n");
			printf("Received length: %lu\n", message->msg_len);
		}
	}
	return ;
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
void	init_message(t_message *message)
{
	message->len_counter = sizeof(size_t) * 8;
	printf("len_counter init to value (size_t * 8 bits): %u\n", message->len_counter);
	return ;
}

