/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:08:45 by jlintune          #+#    #+#             */
/*   Updated: 2023/07/27 19:23:56 by jlintune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
	// PARSE PARAMETERS
	// has to be two
	// VALIDATE PID
	//	conditions for this??
	// VALIDATE MESSAGE: NOT NULL

volatile t_client_state g_client_state;

int	main(int argc, char	*argv[])
{
	t_msg_params	client_message;
	
	if (!parse_inputs(argc, argv))
	{
		return (1);
	}

	return (0);
}

int	parse_inputs(int argc, char	*argv[])
{
	if (argc != 3)
	{
		printf("Incorrect number of arguments\n");
		printf("Correct usage: ./client PID \"String to be sent to server\"\n");
		return (1);
	}


	return (0);
}

