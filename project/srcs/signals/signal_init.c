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

static void sig_handle(int what)
{
	if (what != SIGINT)
		return;
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	quit_flag_set(1);
	
}

int	quit_flag(int *value)
{
	static int	val = 0;

	if (value)
		val = *value;
	return (val);
}

int	quit_flag_set(int value)
{
	return (quit_flag(&value));
}

void	init_signal()
{
	struct sigaction	sighandler;

	sighandler.sa_handler = sig_handle;
	sigemptyset(&sighandler.sa_mask);
	sighandler.sa_flags = 0;

	if (!isatty(STDIN_FILENO))
		return ;
	sigaction(SIGINT, &sighandler, 0);
	sigaction(SIGQUIT, &sighandler, 0);
}
