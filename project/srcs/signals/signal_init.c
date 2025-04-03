/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:48:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

void	kill_sig(int what)
{
	static int		kill = 0;
	static int		stage = 0;
	static size_t	ptr = 0;

	if (what == SIGINT && stage == 0)
	{
		kill = what;
		return ;
	}
	if (stage == 0)
		ptr = ((size_t)what) & 0xFFFFFFFF;
	else if (stage == 1)
	{
		ptr = (ptr) | (((size_t)what) << 32);
		*((int *)ptr) = kill;
		stage = -1;
		kill = 0;
	}
	stage++;
}

t_bool	has_killsig()
{
	int		res;
	size_t	ptr;

	res = 0;
	ptr = (size_t)(&res);
	kill_sig((int)(ptr));
	kill_sig((int)(ptr>>32));
	return (res != 0);
}

void	init_signal()
{
	struct termios		shell_tmodes;
	int					shell_terminal;
	int					shell_is_interactive; 
	struct sigaction	sigIntHandler;

	sigIntHandler.sa_handler = kill_sig;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty (shell_terminal);
	if (shell_is_interactive)
	{
		tcgetattr(shell_terminal, &shell_tmodes);
		sigaction(SIGINT, &sigIntHandler, 0);
		signal(SIGQUIT, SIG_IGN);
	}
}

