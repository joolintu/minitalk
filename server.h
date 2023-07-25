/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:04:09 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/25 03:03:55 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "minitalk.h"

int		main(void);
int		init_signal_handlers(struct sigaction *sa1, struct sigaction *sa2);
void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext);
void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext);
void	signal_parser(t_message	*message);
void	init_message(t_message *message);

#endif