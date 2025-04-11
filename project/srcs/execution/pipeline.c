/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:53:15 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:29:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Goes through the token list to get to the next starting command.
 * 
 * Iterates through the token list and skips tokens until it finds a token that
 * starts a new command, whether it be a pipe or an operator.
 * 
 * @param t Token list.
 * 
 * @return Token list starting at the next command, NULL if no more commands
 * are found.
 */
t_token	*get_to_next_command(t_token *t)
{
	while (t && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == PIPE)
			return (t->nxt);
		t = t->nxt;
	}
	return (t);
}

/**
 * @brief Counts the number of commands in the current execution block.
 * 
 * @param t Token list.
 * 
 * @return Number of commands before encountering an operator.
 */
static int	count_cmds(t_token *t)
{
	int	number;

	number = t != 0;
	while (t && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == PIPE)
			number++;
		t = t->nxt;
	}
	return (number);
}

/**
 * @brief Generates pipes for a pipeline of n commands.
 * 
 * Creates the necessary pipes for a pipeline of commands. A pipeline
 * consisting of `n` commands requires `n - 1` pipes, where each pipe contains
 * an input and output file descriptor. Allocates memory for the required pipe
 * array and returns it.
 * 
 * @param n Number of commands in the pipeline.
 * 
 * @return Allocated array of pipes already piped, NULL if memory allocation
 * fails or pipe creation fails.
 */
static int	*generate_pipes(int n)
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
 * @brief Builds up all the commands ready for execution.
 * 
 * Iterates through the token list and creates the required command structures.
 * Processes each command sequentially, allocating memory for each command and
 * retrieving necessary information. If allocation fails for any command, frees
 * all previously allocated commands and returns NULL.
 * 
 * @param data Pointer to the main data structure.
 * @param t Token list starting at the current execution block.
 * @param n Number of commands to build.
 * 
 * @return Allocated array of commands, NULL if memory allocation fails.
 */
static t_cmd	**get_commands(t_data *data, t_token *t, int n)
{
	int		i;
	t_cmd	**cmds;

	cmds = (t_cmd **)malloc(n * sizeof(t_cmd *));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cmds[i] = get_command(data, t);
		if (!cmds[i])
			return (free_commands(cmds, i));
		t = get_to_next_command(t);
		i++;
	}
	return (cmds);
}

/**
 * @brief Builds a pipeline structure for the current execution block.
 * 
 * Creates and initializes a pipeline structure, which holds information about
 * the pipeline, such as the number of commands, pipes, environment variables
 * and command structures. Also duplicates the standard input and output file
 * descriptors to allow restoration after execution. If any allocation fails
 * during pipeline creation, frees everything previously allocated and returns
 * NULL.
 * 
 * @param data Pointer to the main data structure.
 * @param t Token list starting at the current execution block.
 * 
 * @return Allocated and filled pipeline structure, NULL if memory allocation
 * fails.
 */
t_pipe	*get_pipeline(t_data *data, t_token *t)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->n = count_cmds(t);
	pipe->stdin_backup = dup(STDIN_FILENO);
	pipe->stdout_backup = dup(STDOUT_FILENO);
	pipe->paths = get_paths(data);
	pipe->envp = NULL;
	pipe->pipes = NULL;
	pipe->pids = NULL;
	pipe->cmds = get_commands(data, t, pipe->n);
	if (!pipe->paths || !pipe->cmds)
		return (free_pipeline(pipe));
	if (pipe->n == 1)
		return (pipe);
	pipe->envp = copy_envp(data->vars);
	pipe->pipes = generate_pipes(pipe->n);
	pipe->pids = (pid_t *)malloc(pipe->n * sizeof(pid_t));
	if (!pipe->envp || !pipe->pipes || !pipe->pids)
		return (free_pipeline(pipe));
	return (pipe);
}
