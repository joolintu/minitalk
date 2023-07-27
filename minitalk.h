/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 03:01:53 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/27 07:42:34 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_signal
{
	sig_atomic_t	arrived;
	sig_atomic_t	sigusr_bit;
	sig_atomic_t	ack_target_pid;
}					t_signal;

typedef struct s_server_state
{
	unsigned char	len_counter;
	pid_t			ack_target_pid;
	size_t			msg_len;
	char			*msg_string;
}					t_server_state;

typedef struct s_client_state
{
	sig_atomic_t	ack_ok;
	unsigned int	server_pid;
}					t_client_state;

#endif