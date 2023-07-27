/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:08:45 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/27 21:54:05 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "client.h"
#include "minitalk.h"

#include <string.h> // REMOVE THIS

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

volatile t_msg_params g_client_params;

void sigusr_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_client_params.ack_ok = 1;
	(void)sig;
	(void)ucontext;
	return;
}

int main(int argc, char *argv[])
{
	struct sigaction sa;

	if (validate_and_parse_inputs(argc, argv))
	{
		printf("Validation error\n");
		return (1);
	}
	init_signal_handlers(&sa);
	send_client_pid();
	send_msg_length();
	
	printf("Back from send msg length\n");
	
	send_message();

	printf("End of client main\n");
	return (0);
}

int validate_and_parse_inputs(int argc, char *argv[])
{
	printf("Validate and parse inputs\n");

	if (argc != 3)
	{
		printf("Incorrect number of arguments\n");
		printf("Correct usage: ./client PID \"String to be sent to server\"\n");
		return (1);
	}

	g_client_params.len_counter = sizeof(size_t) * 8;
	g_client_params.other_end_pid = (pid_t)atoi(argv[1]);
	g_client_params.msg_len = strlen(argv[2]);
	g_client_params.msg_string = argv[2];
	g_client_params.ack_ok = 1;

	printf("msg_len: %lu, len_count: %lu, pid: %i, ack: %i", g_client_params.msg_len, g_client_params.len_counter, g_client_params.other_end_pid, g_client_params.ack_ok);
	printf("\t...params set\n");
	return (0);
}

int init_signal_handlers(struct sigaction *sa)
{
	printf("Init signal handlers");
	sa->sa_sigaction = sigusr_handler;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sa->sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
	printf("\t...set\n");
	return (0);
}

void send_client_pid()
{
	printf("Sending first signal, ");
	printf("ack ok: %i, ", g_client_params.ack_ok);
	if (g_client_params.ack_ok)
	{
		printf("other end pid: %i, ", g_client_params.other_end_pid);
		g_client_params.ack_ok = 0;
		kill(g_client_params.other_end_pid, SIGUSR1);
		printf("...sent\n");
	}

	return;
}

void send_msg_length()
{
	volatile unsigned int signal;

	while (g_client_params.len_counter > 0)
	{
		if (g_client_params.ack_ok)
		{
			g_client_params.ack_ok = 0;
			signal = (g_client_params.msg_len >> g_client_params.len_counter - 1) & 1;
			if (signal == 0)
			{
				kill(g_client_params.other_end_pid, SIGUSR1);
			}
			else
			{
				kill(g_client_params.other_end_pid, SIGUSR2);
			}
			g_client_params.len_counter--;
			if (g_client_params.len_counter == 0)
			{
				printf("Length sent.\n");
			}
		}
	}
	return;
}

void send_message()
{
	size_t i;
	char c;

	printf("Sending message\n");
	printf("msg_len: %lu, len_count: %lu, pid: %i, ack: %i\n", g_client_params.msg_len, g_client_params.len_counter, g_client_params.other_end_pid, g_client_params.ack_ok);


	i = 0;
	while (g_client_params.msg_len)
	{
//		printf("msg len: %lu\n", g_client_params.msg_len);
		c = g_client_params.msg_string[i];
		send_char(c);
		g_client_params.msg_len--;
		i++;
	}
	printf("Sending null terminator\n");
	send_char('\0');

	return;
}

void send_char(char c)
{
	int 					shift;
	volatile unsigned int	signal;

	shift = 7;

	printf("sending char %c, ", c);
	while (shift >= 0)
	{
		if (g_client_params.ack_ok)
		{
			g_client_params.ack_ok = 0;
			signal = (c >> shift) & 1;
			if (signal == 0)
			{
				kill(g_client_params.other_end_pid, SIGUSR1);
			}
			else
			{
				kill(g_client_params.other_end_pid, SIGUSR2);
			}
			printf("%i", shift);
			shift--;
		}
	}
	printf("\n");
	return;
}