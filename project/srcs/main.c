/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:01 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/25 15:55:13 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code = 0;

/**
 * @brief Parses and executes a single user command line.
 *
 * Validates the input line, tokenizes and parses it into an AST, executes the
 * command(s), handles cleanup of the AST and pipeline, and updates the shell
 * prompt and line counter.
 *
 * @param line The command line input.
 * @param d    Pointer to the shell data context.
 */
void	run_cmd_from_user(char *line, t_data *d)
{
	if (*line && !ft_stristype(line, ft_isspace) && try_parse_command(line, d))
	{
		d->ast = build_ast(d->tokens);
		if (g_last_exit_code == M_ERR)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		g_last_exit_code = execute_ast(d, d->ast);
		d->pipe = free_pipeline(d->pipe);
		if (g_last_exit_code == M_ERR)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		d->ast = free_ast(d->ast);
	}
	d->line_number++;
}

/**
 * @brief Runs the shell in interactive mode.
 *
 * Continuously prompts the user for input using `readline`, handles signals,
 * and passes valid lines to the command execution function.
 * Exits gracefully on EOF (e.g., Ctrl-D) with last exit code.
 *
 * @param d Pointer to the shell data context.
 */
void	shell_interactive(t_data *d)
{
	char	*line;

	while (1)
	{
		set_signals(1);
		line = readline(get_prompt(d, 1));
		set_signals(0);
		if (!line)
			clean_exit(d, g_last_exit_code);
		run_cmd_from_user(line, d);
		get_prompt(d, 2);
	}
}

/**
 * @brief Runs the shell in non-interactive mode.
 *
 * Reads a single command line from standard input (e.g., from a script or
 * pipe), trims it, and runs it through the normal command execution path.
 * Exits after processing the single line.
 *
 * @param d Pointer to the shell data context.
 */
void	shell_non_interactive(t_data *d)
{
	char	*line;
	char	*trimmed;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (errno == ENOMEM)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		if (!line)
			break ;
		trimmed = ft_strtrim(line, "\n");
		free_str(&line);
		if (!trimmed)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		run_cmd_from_user(trimmed, d);
	}
}

/**
 * @brief Minishell's entry point.
 *
 * Initializes the shell data structure, detects whether the shell should run
 * in interactive or non-interactive mode, and dispatches accordingly. Frees
 * all resources on exit and returns the last command's exit status.
 *
 * @param argc Argument count (unused).
 * @param argv Argument values (shell name may be reset).
 * @param envp Environment variable array.
 * 
 * @return int The last command's exit code.
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (errmsg("minishell: arguments are not supported\n", 0, 0, 1));
	argv[0] = 0;
	if (!data_init(&data, envp))
		clean_exit(&data, errmsg(M_ERR_MSG, 0, 0, 1));
	if (isatty(STDIN_FILENO))
		shell_interactive(&data);
	else
		shell_non_interactive(&data);
	free_data(&data);
	return (g_last_exit_code);
}
