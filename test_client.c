/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:08:45 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/26 03:28:29 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "client.h"
#include "minitalk.h"

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
	// PARSE PARAMETERS
	// has to be two
	// VALIDATE PID
	//	conditions for this??
	// VALIDATE MESSAGE: NOT NULL

volatile t_client_state g_client_state;

void	sigusr_handler(int sig, siginfo_t *info, void *ucontext)
{
//	printf(" ACK incoming\n");
	g_client_state.ack_ok = 1;
	(void)sig;
	(void)ucontext;
	return ;
}

int	main(int argc, char	*argv[])
{
	t_message	client_message;
	struct sigaction	sa;

	sa.sa_sigaction = sigusr_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// if (!parse_inputs(argc, argv))
	// {
	// 	return (1);
	// }

	client_message.msg_len = 1023;
	client_message.len_counter = sizeof(size_t) * 8;
	g_client_state.server_pid = atoi(argv[1]);
	g_client_state.ack_ok = 1;

	size_t	bitmask;
	bitmask = -1;
	unsigned char signal;

	while (1)
	{
		if (g_client_state.ack_ok)
		{
			g_client_state.ack_ok = 0;
			if (client_message.len_counter >= 0)
			{
				signal = (client_message.msg_len >> client_message.len_counter - 1) & 1;
//				printf("sig %i, len_counter %i\n", signal, client_message.len_counter);
				if (signal == 0)
				{
					kill(g_client_state.server_pid, SIGUSR1);
				}
				else
				{
					kill(g_client_state.server_pid, SIGUSR2);
				}
				if (client_message.len_counter == 0)
				{
					printf("Length sent.\n");
					break;
				}
				client_message.len_counter--;
			}
		}
	}

	return (0);
}

int	parse_inputs(int argc, char	*argv[])
{
	if (argc != 3)
	{
		printf("Incorrect number of arguments\n");
		printf("Correct usage: ./client PID \"String to be sent to server\"\n");
		return (1);
	}

	

	return (0);
}



