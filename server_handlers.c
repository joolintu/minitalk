/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sighandlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:15:55 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/28 04:16:51 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "server.h"

void	sigfirst_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_signal_data.arrived = 1;
	g_signal_data.other_end_pid = info->si_pid;
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
