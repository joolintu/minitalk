/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:08:45 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/28 04:21:43 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "minitalk.h"

volatile t_msg_params	g_client_params;

void	sigusr_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_client_params.ack_ok = 1;
	(void)sig;
	(void)ucontext;
	return ;
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	if (validate_and_parse_inputs(argc, argv))
	{
		printf("Correct usage: ./client PID \"String to server\"\n"); //REPLACE
		return (1);
	}
	init_signal_handlers(&sa);
	send_client_pid();
	send_msg_length();
	send_message();
	return (0);
}

int	validate_and_parse_inputs(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Incorrect number of arguments\n"); //Replace
		return (1);
	}
	g_client_params.other_end_pid = (pid_t)atoi(argv[1]); // TODO ft_atoi
	if (g_client_params.other_end_pid <= 1)
	{
		printf("Incorrect process ID. Don\'t do that please.\n"); //Replace
		return (2);
	}
	if (kill(g_client_params.other_end_pid, 0))
	{
		printf("Error sending signal to Process ID %i\n", 
			g_client_params.other_end_pid); //Replace
		return (3);
	}
	g_client_params.len_counter = sizeof(size_t) * 8;
	g_client_params.msg_len = strlen(argv[2]); //Replace
	g_client_params.msg_string = argv[2];
	g_client_params.ack_ok = 1;
	return (0);
}

int	init_signal_handlers(struct sigaction *sa)
{
	sa->sa_sigaction = sigusr_handler;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sa->sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
	return (0);
}
