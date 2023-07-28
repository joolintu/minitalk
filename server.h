/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:04:09 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/28 04:28:29 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "minitalk.h"

extern volatile t_signal	g_signal_data;

int		main(void);
void	sigfirst_handler(int sig, siginfo_t *info, void *ucontext);
void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext);
void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext);
int		init_signal_handlers(struct sigaction 
			*sa1, struct sigaction 
			*sa2, struct sigaction *saf);
void	init_message(t_msg_params *msg_params);
void	parse_client_pid(t_msg_params *msg_params, struct sigaction *sa1);
void	parse_length(t_msg_params	*msg_params);
void	parse_string(t_msg_params	*msg_params);
void	put_string(t_msg_params	*msg_params);
char	parse_char(void);
void	init_message(t_msg_params	*msg_params);
void	reset_first_handler(struct sigaction *sa);

#endif