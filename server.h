/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:04:09 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/24 20:12:52 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_signal
{
	sig_atomic_t	arrived;
	sig_atomic_t	sigusr_bit;
	sig_atomic_t	ack_target_pid;
}					t_signal;

typedef struct s_message
{
	unsigned char	len_counter;
//	unsigned char	cont_counter;
	size_t			msg_len;
//	unsigned char	msg_continue;
	char			*msg_string;
}					t_message;

int		main(void);
int		init_signal_handlers(struct sigaction *sa1, struct sigaction *sa2);
void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext);
void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext);
void	signal_parser(t_message	*message);
void	init_message(t_message *message);

#endif