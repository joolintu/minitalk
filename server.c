/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:02:50 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/31 22:30:37 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "server.h"

volatile t_signal	g_signal_data;

int	main(void)
{
	struct sigaction	saf;
	struct sigaction	sa1;
	struct sigaction	sa2;
	static t_msg_params	msg_params;

	if (init_signal_handlers(&sa1, &sa2, &saf) != 0)
	{
		return (1);
	}
	init_message(&msg_params);
	ft_printf("Minitalk TEST Server PID: %d\n", getpid());
	while (1)
	{
		parse_client_pid(&msg_params, &sa1);
		parse_length(&msg_params);
		parse_string(&msg_params);
		put_string(&msg_params);
		init_message(&msg_params);
		reset_first_handler(&saf);
	}
	return (0);
}

void	put_string(t_msg_params *msg_params)
{
	ft_printf("%s\n", msg_params->msg_string);
}

void	reset_first_handler(struct sigaction *saf)
{
	sigaction(SIGUSR1, saf, NULL);
}

int	init_signal_handlers(struct sigaction *sa1,
						struct sigaction *sa2,
						struct sigaction *saf)
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

void	init_message(t_msg_params *msg_params)
{
	msg_params->other_end_pid = 0;
	msg_params->len_counter = sizeof(size_t) * 8;
	if (msg_params->msg_string)
	{
		free(msg_params->msg_string);
	}
	msg_params->msg_string = NULL;
	if (msg_params->msg_len)
	{
		msg_params->msg_len = 0;
	}
	return ;
}
