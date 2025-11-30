/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:01 by pkurt             #+#    #+#             */
/*   Updated: 2025/11/30 22:24:29 by ego              ###   ########.fr       */
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
 * @param d Pointer to the main data structure.
 */
static void	run_cmd_from_user(char **line, t_data *d)
{
	if (**line && !ft_stristype(*line, ft_isspace)
		&& try_parse_command(line, d))
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
 * @brief Handles the `-c` option for non-interactive command execution.
 *
 * If the user passes `-c <command>` on the command line (e.g. `./minishell -c
 * "echo hi"`), this function copies the command string into `d->line`, assigns
 * positional parameters ($0, $1, $2, ...) as local variables, and then
 * executes the command.
 *
 * Positional arguments (argv[3] and onwards) are assigned as:
 * @brief - $0 → argv[3]
 * @brief - $1 → argv[4]
 * @brief - etc.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param d Pointer to the main data structure.
 */
static void	shell_c_option(int argc, char **argv, t_data *d)
{
	int		i;
	char	*id;

	if (argc == 2)
		return ((void)errmsg_prefix("-c", "option requires an argument", 2));
	d->line = ft_strdup(argv[2]);
	if (!d->line)
		clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
	i = 3;
	while (i < argc)
	{
		id = ft_itoa(i - 3);
		if (!id)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		if (!var_set(&d->vars, id, argv[i], LOCAL))
		{
			free_str(&id);
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		}
		free_str(&id);
		i++;
	}
	run_cmd_from_user(&d->line, d);
}

/**
 * @brief Runs the shell in interactive mode.
 *
 * Continuously prompts the user for input using `readline`, handles signals,
 * and passes valid lines to the command execution function.
 * Exits gracefully on EOF (e.g., Ctrl-D) with last exit code.
 *
 * @param d Pointer to the main data structure.
 */
static void	shell_interactive(t_data *d)
{
	while (1)
	{
		set_signals(1);
		d->line = readline(get_prompt(d, 1));
		set_signals(0);
		if (!d->line)
			clean_exit(d, g_last_exit_code);
		run_cmd_from_user(&d->line, d);
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
 * @param d Pointer to the main data structure.
 */
static void	shell_non_interactive(t_data *d)
{
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(STDIN_FILENO);
		if (errno == ENOMEM)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		if (!tmp)
			break ;
		d->line = ft_strtrim(tmp, "\n");
		free_str(&tmp);
		if (!d->line)
			clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
		run_cmd_from_user(&d->line, d);
	}
}

/**
 * @brief Minishell's entry point.
 *
 * Initializes the main data structure, sets up environment variables, and
 * chooses the appropriate execution mode:
 * @brief - Interactive mode: if no arguments are provided (`argc == 1`) and
 * the shell is connected to a terminal (`isatty(STDIN_FILENO)`), the shell
 * enters an interactive readline loop, displaying a prompt and executing user
 * input.
 * @brief - Non-interactive mode: if no arguments are provided but stdin is not
 * a terminal, the shell reads and executes a single line from stdin.
 * @brief - Command option: if `-c` is passed as the first argument (e.g.
 * `./minishell -c "echo hello"`), the shell executes the provided command. Any
 * subsequent arguments are assigned as positional parameters ($0, $1, ...).
 * @brief - Invalid usage: any other argument pattern results in a help message
 * being displayed and an error code returned.
 *
 * On exit, all dynamically allocated resources are freed, and the shell returns
 * the exit status of the last executed command.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @param envp Environment variable array.
 *
 * @return int Exit status of the last executed command or error code.
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!data_init(&data, envp))
		clean_exit(&data, errmsg(M_ERR_MSG, 0, 0, 1));
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
			shell_interactive(&data);
		else
			shell_non_interactive(&data);
	}
	else if (argc >= 2 && !ft_strcmp(argv[1], "-c"))
		shell_c_option(argc, argv, &data);
	else
		g_last_exit_code = errmsg(HELP_MSG, 0, 0, 2);
	free_data(&data);
	return (g_last_exit_code);
}
