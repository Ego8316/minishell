/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:12:00 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 15:23:25 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief Simple switch to handle builtins.
 * 
 * @param data Pointer to the data structure.
 * @param argv Command's argv.
 * 
 * @return Whatever the builtin returns, -1 if the command
 * is not a builtin.
 */
static int	execute_builtin(t_data *data, char **argv)
{
	if (!ft_strcmp(*argv, "cd"))
		return (cd_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "echo"))
		return (echo_builtin(argv + 1));
	if (!ft_strcmp(*argv, "env"))
		return (env_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "exit"))
		return (exit_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "export"))
		return (export_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "pwd"))
		return (pwd_builtin(data, argv + 1));
	if (!ft_strcmp(*argv, "unset"))
		return (unset_builtin(data, argv + 1));
	return (-1);
}

/**
 * @brief Tries and execute an extern command.
 * 
 * @param data Pointer to the data structure.
 * @param argv Command's argv.
 * 
 * @return Command's exit code, 127 if command not found
 * and -2 if allocation fails.
 */
static int	execute_extern(t_data *data, char **argv)
{
	(void)data;
	// execve(argv[0], argv, data->envp);
	(void)argv;
	return (1);
}

/**
 * @brief Executes a single command (not in a pipeline).
 * Builds a command structure for the current command
 * and exits the whole program if there is an allocation
 * error. Otherwise, actually executes the command with
 * redirections.
 * 
 * @param data Pointer to the data structure.
 * @param t Token list starting at the command to execute.
 * 
 * @return Status code of the command.
 */
int	execute_command(t_data *data, t_token *t)
{
	t_cmd	*cmd;
	int		ret;
	pid_t	pid;

	ret = 0;
	cmd = get_command(data, t);
	int	stdin_backup = dup(STDIN_FILENO);
	int	stdout_backup = dup(STDOUT_FILENO);
	if (!cmd || (!*cmd->argv && !do_assignments(t, data->vars)))
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (*cmd->argv)
	{
		ret = execute_builtin(data, cmd->argv);
		if (ret == -1)
		{
			pid = fork();
			if (pid == 0)
				return (execute_extern(data, cmd->argv));
		}
	}
	if (cmd->fd_in != -1)
		dup2(stdin_backup, STDIN_FILENO);
	if (cmd->fd_out != -1)
		dup2(stdout_backup, STDOUT_FILENO);
	free_command(cmd);
	return (ret);
}

/**
 * @brief Executes a pipeline.
 * 	- Counts the number of commands.
 * 	- Creates all pipes required.
 */
int	execute_pipeline(t_data *data, t_token *t)
{
	t_pipe	*pipeline;

	pipeline = get_pipeline(data, t);
	if (!pipeline)
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	return (0);
}
