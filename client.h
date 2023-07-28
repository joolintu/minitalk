/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:10:12 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/28 04:31:54 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include "minitalk.h"

extern volatile t_msg_params	g_client_params;

int		main(int argc, char	*argv[]);
void	sigusr_handler(int sig, siginfo_t *info, void *ucontext);
int		validate_and_parse_inputs(int argc, char *argv[]);
int		init_signal_handlers(struct sigaction *sa);
void	send_client_pid(void);
void	send_msg_length(void);
void	send_message(void);
void	send_char(char c);
#endif