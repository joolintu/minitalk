/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:04:09 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/27 08:20:25 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "minitalk.h"

int		main(void);
void	sigfirst_handler(int sig, siginfo_t *info, void *ucontext);
void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext);
void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext);
int		init_signal_handlers(struct sigaction *sa1, struct sigaction *sa2, struct sigaction *saf);
void	init_message(t_server_state *message);
void	parse_client_pid(t_server_state *message, struct sigaction *sa1);
void	parse_length(t_server_state	*message);
void	parse_string(t_server_state	*message);
void	put_string(t_server_state	*message);
void	init_message(t_server_state	*message);
void	reset_first_handler(struct sigaction *sa);

#endif