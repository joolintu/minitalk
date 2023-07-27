/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:02:50 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/28 01:29:17 by jlintune         ###   ########.fr       */
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
	static t_msg_params	msg_params;

	if (init_signal_handlers(&sa1, &sa2, &saf) != 0)
	{
		return (1);
	}
	init_message(&msg_params);
	printf("Minitalk TEST Server PID: %d\n", getpid()); // TODO: replace with FT-version
	while (1)
	{
		parse_client_pid(&msg_params, &sa1);
		parse_length(&msg_params);
		parse_string(&msg_params);
		put_string(&msg_params);
		init_message(&msg_params);
		reset_first_handler(&saf); // This could be inside init_message?
	}
	return (0);
}

void	parse_client_pid(t_msg_params *msg_params, struct sigaction *sa1)
{
	printf("Ready to parse client PID\n");
	while (1)
	{
		if (g_signal_data.arrived)
		{
			g_signal_data.arrived = 0;
			msg_params->other_end_pid = g_signal_data.ack_target_pid;
			printf("Set ACK target PID to %i\n", msg_params->other_end_pid);
			sigaction(SIGUSR1, sa1, NULL);
			printf("Set signal handler of SIGUSR1 to sa1\n");
			kill(msg_params->other_end_pid, SIGUSR1);
			break;
		}
	}
	return ;
}

void	parse_length(t_msg_params	*msg_params)
{
	printf("Receive and parse msg_params length\n");
	
	while (msg_params->len_counter > 0)
	{
		if (g_signal_data.arrived == 1)
		{
			printf("%i", (int)g_signal_data.sigusr_bit);
			msg_params->msg_len = (msg_params->msg_len << 1) | g_signal_data.sigusr_bit;
			msg_params->len_counter--;
			g_signal_data.arrived = 0;

			if (msg_params->len_counter == 0)
			{
				printf("\nReceived length: %lu\n", msg_params->msg_len);
				msg_params->msg_string = (char *)malloc(sizeof(char) * msg_params->msg_len + 1);
				printf("Mallocd %lu + 1 for msg_string.\n", msg_params->msg_len);
			}
			kill(g_signal_data.ack_target_pid, SIGUSR1);
		}
	}
	return ;
}
void	parse_string(t_msg_params *msg_params)
{
	printf("Parse string\n");
	printf("msg_len: %lu, len_count: %lu, pid: %i, ack: %i\n", msg_params->msg_len, msg_params->len_counter, msg_params->other_end_pid, msg_params->ack_ok);

	size_t	i;
	char	c;

	if (!msg_params->msg_string)
	{
		printf("ERROR: Message string NULL\n");
	}

	i = 0;
	c = 0;
	while (msg_params->msg_len)
	{
		c = parse_char(&msg_params);
		printf("got char %c\n", c);
		msg_params->msg_string[i] = c;
		msg_params->msg_len--;
		i++;
	}
	printf("Receiving null terminator\n");
	c = parse_char(&c);
	msg_params->msg_string[i] = '\0';

	printf("Transmission complete.\n");

	return ;
}

char	parse_char(t_msg_params	*msg_params)
{
	printf("Parsing char...");

	int	shift;
	char	c;

	shift = 7;
	c = 0;
	while (shift >= 0)
	{
		if (g_signal_data.arrived == 1)
		{
			g_signal_data.arrived = 0;
			if (g_signal_data.sigusr_bit)
			{
				printf("1");
			}
			else 
			{
				printf("0");
			}
			c = c | g_signal_data.sigusr_bit << shift;
			shift--;
			kill(g_signal_data.ack_target_pid, SIGUSR1);
		}
	}

	printf(" returning \'%i\'\n", (int)c);
	return (c);
}
void	put_string(t_msg_params *msg_params)
{
	printf("Put string\n");
	printf("%s\n", msg_params->msg_string);
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
void	init_message(t_msg_params *msg_params)
{
	msg_params->other_end_pid = 0;
	msg_params->len_counter = sizeof(size_t) * 8;
	printf("len_counter init to value (size_t * 8 bits): %lu\n", msg_params->len_counter);

	if (msg_params->msg_string)
	{
		free(msg_params->msg_string);
		printf("Called free() on previous msg_string\n");
	}
	msg_params->msg_string = NULL;
	printf("msg_string init to %s\n", msg_params->msg_string);
	if (msg_params->msg_len)
	{
		msg_params->msg_len = 0;
		printf("msg_len init to 0\n");
	}
	return ;
}

