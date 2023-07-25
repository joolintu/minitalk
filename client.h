/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:10:12 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/25 03:04:32 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "minitalk.h"

int	main(int argc, char	*argv[]);
int	parse_inputs(int argc, char	*argv[]);

#endif