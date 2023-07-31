/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 03:01:53 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/31 23:02:48 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h> // getpid, NULL
# include <signal.h> // sigaction, t_siginfo
# include "./Libft/libft.h"

typedef struct s_signal
{
	sig_atomic_t	arrived;
	sig_atomic_t	sigusr_bit;
	sig_atomic_t	other_end_pid;
}					t_signal;

typedef struct s_msg_params
{
	size_t			len_counter;
	pid_t			other_end_pid;
	size_t			msg_len;
	char			*msg_string;
	sig_atomic_t	ack_ok;
}					t_msg_params;

#endif