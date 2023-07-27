/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:02:50 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/27 08:46:23 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "server.h"


volatile t_signal	g_signal_data;

void	sigfirst_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_signal_data.arrived = 1;
	g_signal_data.ack_target_pid = info->si_pid;
	(void)sig;
	(void)ucontext;
	return ;
}

void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_signal_data.sigusr_bit = 0;
	g_signal_data.arrived = 1;
	(void)sig;
	(void)ucontext;
	return ;
}

void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_signal_data.sigusr_bit = 1;
	g_signal_data.arrived = 1;
	(void)sig;
	(void)ucontext;
	return ;
}

int	main(void)
{
	struct sigaction	saf;
	struct sigaction	sa1;
	struct sigaction	sa2;
	static t_server_state	message;

	if (init_signal_handlers(&sa1, &sa2, &saf) != 0)
	{
		return (1);
	}
	init_message(&message);
	printf("Minitalk TEST Server PID: %d\n", getpid()); // TODO: replace with FT-version
	while (1)
	{
		parse_client_pid(&message, &sa1);
		parse_length(&message);
		parse_string(&message);
		put_string(&message);
		init_message(&message);
		reset_first_handler(&saf); // This could be inside init_message?
	}
	return (0);
}

void	parse_client_pid(t_server_state *message, struct sigaction *sa1)
{
	while (1)
	{
		if (g_signal_data.arrived)
		{
			g_signal_data.arrived = 0;
			message->ack_target_pid = g_signal_data.ack_target_pid;
			printf("Set ACK target PID to %i\n", message->ack_target_pid);
			sigaction(SIGUSR1, sa1, NULL);
			printf("Set signal handler of SIGUSR1 to sa1\n");
			kill(message->ack_target_pid, SIGUSR1);
			break;
		}
	}
	return ;
}

void	parse_length(t_server_state	*message)
{
	printf("Receive and parse message length\n");
	
	while (message->len_counter >= 0)
	{
		if (g_signal_data.arrived == 1)
		{
			printf("%i", (int)g_signal_data.sigusr_bit);
			message->msg_len = (message->msg_len << 1) | g_signal_data.sigusr_bit;
			message->len_counter--;
			g_signal_data.arrived = 0;

			if (message->len_counter == 0)
			{
				printf("\nReceived length: %lu\n", message->msg_len);
				message->msg_string = (char *)malloc(sizeof(char) * message->msg_len + 1);
				printf("Mallocd %lu + 1 for msg_string.\n", message->msg_len);
			}
			kill(g_signal_data.ack_target_pid, SIGUSR1);
		}

	}
	return ;
}
void	parse_string(t_server_state *message)
{

}
void	put_string(t_server_state *message)
{

}

void	reset_first_handler(struct sigaction *saf)
{
	sigaction(SIGUSR1, saf, NULL);
}


int	init_signal_handlers(struct sigaction *sa1, struct sigaction *sa2, struct sigaction *saf)
{
	int	errors;

	errors = 0;
	saf->sa_sigaction = sigfirst_handler;
	errors += sigemptyset(&saf->sa_mask);
	errors += sigaddset(&saf->sa_mask, SIGUSR1);
	errors += sigaddset(&saf->sa_mask, SIGUSR2);
	saf->sa_flags = SA_SIGINFO;

	sa1->sa_sigaction = sigusr1_handler;
	errors += sigemptyset(&sa1->sa_mask);
	errors += sigaddset(&sa1->sa_mask, SIGUSR1);
	errors += sigaddset(&sa1->sa_mask, SIGUSR2);
	sa1->sa_flags = SA_SIGINFO;

	sa2->sa_sigaction = sigusr2_handler;
	errors += sigemptyset(&sa2->sa_mask);
	errors += sigaddset(&sa2->sa_mask, SIGUSR1);
	errors += sigaddset(&sa2->sa_mask, SIGUSR2);
	sa2->sa_flags = SA_SIGINFO;

	errors += -(sigaction(SIGUSR1, saf, NULL));
	errors += -(sigaction(SIGUSR2, sa2, NULL));
	return (errors);
}
void	init_message(t_server_state *message)
{
	message->ack_target_pid = 0;
	message->len_counter = sizeof(size_t) * 8;
	printf("len_counter init to value (size_t * 8 bits): %u\n", message->len_counter);

	if (message->msg_string)
	{
		free(message->msg_string);
		printf("Called free() on previous msg_string\n");
	}
	message->msg_string = NULL;
	printf("msg_string init to %s\n", message->msg_string);
	if (message->msg_len)
	{
		message->msg_len = 0;
		printf("msg_len init to 0\n");
	}
	return ;
}

