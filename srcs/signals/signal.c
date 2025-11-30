/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:22:18 by ego               #+#    #+#             */
/*   Updated: 2025/05/23 16:07:45 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Ignores SIGQUIT (Ctrl-\) signal.
 */
void	ignore_sigquit(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

/**
 * @brief Resets the readline prompt when receiving SIGINT (Ctrl-C).
 * 
 * @param signo Signal number (unused).
 */
void	reset_prompt(int signo)
{
	(void)signo;
	g_last_exit_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Prints a newline and sets exit code to 130.
 * 
 * @param signo Signal number (unused).
 */
void	print_newline(int signo)
{
	(void)signo;
	g_last_exit_code = 130;
	printf("\n");
	rl_on_new_line();
}

/**
 * @brief Prints a newline and sets exit code to `HEREDOC_C`.
 * 
 * @param signo Signal number (unused).
 */
void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_last_exit_code = HEREDOC_C;
	printf("\n");
}

/**
 * @brief Sets signal handlers based on the given mode.
 * 
 * @brief - 0: non-interactive mode - SIGINT and SIGQUIT print a newline.
 * @brief - 1: interactive mode - SIGQUIT is ignored, and SIGINT resets the
 * readline prompt.
 * @brief - 2: heredoc mode - SIGQUIT is ignored, SIGINT prints a newline and
 * sets the global exit code to `HEREDOC_C` to handle Ctrl-C in heredocs.
 * 
 * @param mode Signal mode to apply: 0 for non-interactive, 1 for interactive,
 * 2 for heredoc input.
 */
void	set_signals(int mode)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	if (mode == 0)
	{
		sig.sa_handler = &print_newline;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
	if (mode == 1)
	{
		ignore_sigquit();
		sig.sa_handler = &reset_prompt;
		sigaction(SIGINT, &sig, NULL);
	}
	if (mode == 2)
	{
		ignore_sigquit();
		sig.sa_handler = &heredoc_sigint_handler;
		sigaction(SIGINT, &sig, NULL);
	}
}
