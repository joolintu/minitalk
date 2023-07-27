/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:10:12 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/27 08:11:45 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "minitalk.h"

int	main(int argc, char	*argv[]);
void	sigusr_handler(int sig, siginfo_t *info, void *ucontext);
int		init_signal_handlers(struct sigaction *sa);
int	parse_inputs(int argc, char	*argv[]);

#endif