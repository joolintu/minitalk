/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:01:39 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/22 18:31:08 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	PROTOCOL OUTLINES
	1) HEADER
	- MESSAGE SIZE, in chars, sizeof(int) (24 bits)
	- CONTINUE in next batch, 1 bit
	- PARITY, 1 bit
	2) MESSAGE
	- RESEND FLAG, 1 bit
	- DATA, 8 bits
	- PARITY, 1 bit
*/

/*
	TRANSMIT STATE, enum
	INIT -1,
	RESEND FLAG 0,
	DATA 1,
	PARITY FLAG 2.

	stage = ++stage % 3
*/

#include "server.h"

/*
	Allowed stuff:
	- write
	- ft_printf
	- signal
	- sigemptyset
	- sigaddset
	- sigaction
	- kill
	- getpid
	- malloc
	- free
	- pause
	- sleep
	- usleep
	- exit
*/

int	main(int argc, char	*argv[])
{
	// GET PROCESS ID
	// PARSE IT
	// PRINT IT

	return (0);
}
