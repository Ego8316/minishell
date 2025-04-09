/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:48:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void int_handler(int what)
{
	if (what != SIGINT)
		return ;
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	//printf("interrupt signal");
}

int	is_exiting(int *value)
{
	static int	val = 0;

	if (value)
		val = *value;
	return (val);
}

static void quit_handler(int what)
{
	struct sigaction	sigQuitHandler;

	if (what != SIGQUIT)
		return ;
	if (is_exiting(0) != 0)
		return ;
	sigQuitHandler.sa_handler = quit_handler;
	sigemptyset(&sigQuitHandler.sa_mask);
	sigQuitHandler.sa_flags = SA_RESETHAND;
	sigaction(SIGQUIT, &sigQuitHandler, 0);
}

void	init_signal()
{
	int					shell_is_interactive; 
	struct sigaction	sigIntHandler;

	sigIntHandler.sa_handler = int_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	shell_is_interactive = isatty(STDIN_FILENO);
	if (shell_is_interactive)
	{
		sigaction(SIGINT, &sigIntHandler, 0);
		signal(SIGQUIT, SIG_IGN);
	}
}
