/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:53:15 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 01:01:01 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Simple switch to handle builtins.
 * 
 * @param data Pointer to the data structure.
 * @param cmd Token corresponding to the current command.
 * 
 * @return Whatever the builtin returns, -1 if the command
 * is not a builtin.
 */
int	execute_builtin(t_data *data, t_token *cmd)
{
	if (!ft_strcmp(cmd->str, "cd"))
		return (cd_builtin(data, cmd->nxt));
	if (!ft_strcmp(cmd->str, "echo"))
		return (echo_builtin(cmd->nxt));
	if (!ft_strcmp(cmd->str, "env"))
		return (env_builtin(data, cmd->nxt));
	if (!ft_strcmp(cmd->str, "exit"))
		return (exit_builtin(data, cmd->nxt));
	if (!ft_strcmp(cmd->str, "export"))
		return (export_builtin(data, cmd->nxt));
	if (!ft_strcmp(cmd->str, "pwd"))
		return (pwd_builtin(data, cmd->nxt));
	if (!ft_strcmp(cmd->str, "unset"))
		return (unset_builtin(data, cmd->nxt));
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
int	count_commands(t_token *cmds)
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

// /**
//  * @brief Gathers data for the current command in the pipeline.
//  * Allocates memory for a command structure and fields it.
//  * 
//  * @return The allocated command structure, NULL if allocation fails.
//  */
// t_command	*parse_command(t_token *tokens)
// {
// 	t_command	*cmd;
// 	t_token		*t;
// 	int			args;

// 	cmd = (t_command *)malloc(sizeof(t_command));
// 	if (!cmd)
// 		return (NULL);
// 	t = tokens;
// 	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
// 	{
// 		if (t->type == TEXT)
// 			args++;
// 		if (t->type >= REDIRIN && t->type <= INDELI)
// 		{
// 			get_files(t->nxt->str, t->type);
// 			t = t->nxt;
// 		}
// 		t = t->nxt;
// 	}
// }

// /**
//  * @brief Parses the pipeline execution block
//  * and gets everything ready for execution.
//  *	- Counts the number of commands.
//  *	- For each command, gets the redirections.
//  *	- Creates all pipes required.
//  *	- Creates the PID array.
//  */
// int	generate_pipeline(t_data *data, t_token *cmds)
// {

// }

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

	n = count_commands(cmds);
	pipes = generate_pipes(n);
	pids = (int *)malloc(n * sizeof(int));
	if (!pipes || !pids)
		clean_exit(data, 1);
	return (0);
}
