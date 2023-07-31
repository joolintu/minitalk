/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:14:08 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/31 22:34:34 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "server.h"

void	parse_client_pid(t_msg_params *msg_params, struct sigaction *sa1)
{
	while (1)
	{
		if (g_signal_data.arrived)
		{
			g_signal_data.arrived = 0;
			msg_params->other_end_pid = g_signal_data.other_end_pid;
			sigaction(SIGUSR1, sa1, NULL);
			kill(msg_params->other_end_pid, SIGUSR1);
			break ;
		}
	}
	return ;
}

void	parse_length(t_msg_params	*msg_params)
{
	while (msg_params->len_counter > 0)
	{
		if (g_signal_data.arrived == 1)
		{
			msg_params->msg_len
				= (msg_params->msg_len << 1) | g_signal_data.sigusr_bit;
			msg_params->len_counter--;
			g_signal_data.arrived = 0;
			if (msg_params->len_counter == 0)
			{
				msg_params->msg_string
					= (char *)malloc(sizeof(char) * msg_params->msg_len + 1);
				// PROTECT this malloc
			}
			kill(g_signal_data.other_end_pid, SIGUSR1);
		}
	}
	return ;
}

void	parse_string(t_msg_params *msg_params)
{
	size_t	i;
	char	c;

	if (!msg_params->msg_string)
	{
		ft_printf("ERROR: Message string NULL\n");
	}
	i = 0;
	c = 0;
	while (msg_params->msg_len)
	{
		c = parse_char();
		msg_params->msg_string[i] = c;
		msg_params->msg_len--;
		i++;
	}
	c = parse_char();
	msg_params->msg_string[i] = c;
	return ;
}

char	parse_char(void)
{
	int		shift;
	char	c;

	shift = 7;
	c = 0;
	while (shift >= 0)
	{
		if (g_signal_data.arrived == 1)
		{
			g_signal_data.arrived = 0;
			c = c | g_signal_data.sigusr_bit << shift;
			shift--;
			kill(g_signal_data.other_end_pid, SIGUSR1);
		}
	}
	return (c);
}
