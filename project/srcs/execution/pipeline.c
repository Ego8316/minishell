/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:53:15 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 14:22:45 by ego              ###   ########.fr       */
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
int	execute_builtin(t_data *data, char **argv)
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
 * @brief From the given starting point of the token list, counts
 * the number of commands.
 * 
 * @param cmds Token list.
 * 
 * @return The number of commands before encountering a boolean operator.
 */
int	count_cmds(t_token *cmds)
{
	int	number;

	number = cmds != 0;
	while (cmds && cmds->type != ANDOPER && cmds->type != OROPER)
	{
		if (cmds->type == PIPE)
			number++;
		cmds = cmds->nxt;
	}
	return (number);
}

/**
 * @brief Generates pipes for a pipeline of n commands.
 * Allocates memory for an int array of size 2(n - 1),
 * because we need n - 1 pipes for n commands and each
 * pipe has one input and one output.
 * 
 * @param n The number of commands.
 * 
 * @return Allocated array of pipes already piped. NULL
 * if allocations or pipe fails.
 */
int	*generate_pipes(int n)
{
	int	*pipes;
	int	i;

	pipes = (int *)malloc(2 * (n - 1) * sizeof(int));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipes + 2 * i) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

/**
 * @brief Executes a single command (not in a pipeline).
 * Builds a command structure for the current command
 * and exits the whole program if there is an allocation
 * error. Otherwise, actually executes the command with
 * redirections.
 * 
 * @param data Pointer to the data structure.
 * @param cmds Token list starting at the command to execute.
 * 
 * @return Status code of the command.
 */
int	execute_command(t_data *data, t_token *cmds)
{
	t_cmd	*cmd;

	cmd = get_command(data, cmds);
	if (!cmd)
		clean_exit(data, errmsg("malloc: failed allocation\n", 0, 0, 1));
	if (!*cmd->argv)
		do_assignments(cmds, data->vars);
	else
		execute_builtin(data, cmd->argv);
	free_command(cmd);
	return (0);
}

/**
 * @brief Executes a pipeline.
 * 	- Counts the number of commands.
 * 	- Creates all pipes required.
 */
int	execute_pipeline(t_data *data, t_token *cmds)
{
	int	n;
	int	*pipes;
	int	*pids;

	n = count_cmds(cmds);
	pipes = generate_pipes(n);
	pids = (int *)malloc(n * sizeof(int));
	if (!pipes || !pids)
		clean_exit(data, 1);
	return (0);
}
