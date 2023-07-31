/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_senders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:18:27 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/31 22:32:42 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "minitalk.h"

void	send_client_pid(void)
{
	if (g_client_params.ack_ok)
	{
		g_client_params.ack_ok = 0;
		kill(g_client_params.other_end_pid, SIGUSR1);
	}
	return ;
}

void	send_msg_length(void)
{
	volatile int	signal;

	while (g_client_params.len_counter > 0)
	{
		if (g_client_params.ack_ok)
		{
			g_client_params.ack_ok = 0;
			signal = (g_client_params.msg_len
					>> (g_client_params.len_counter - 1)) & 1;
			if (signal == 0)
			{
				kill(g_client_params.other_end_pid, SIGUSR1);
			}
			else
			{
				kill(g_client_params.other_end_pid, SIGUSR2);
			}
			g_client_params.len_counter--;
		}
	}
	return ;
}

void	send_message(void)
{
	size_t	i;
	char	c;

	i = 0;
	while (g_client_params.msg_len)
	{
		c = g_client_params.msg_string[i];
		send_char(c);
		g_client_params.msg_len--;
		i++;
	}
	send_char('\0');
	return ;
}

void	send_char(char c)
{
	int				shift;
	volatile int	signal;

	shift = 7;
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
			shift--;
		}
	}
	return ;
}
