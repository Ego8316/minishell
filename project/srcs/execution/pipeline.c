/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:53:15 by ego               #+#    #+#             */
/*   Updated: 2025/04/06 15:26:14 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief From the given starting point of the token list, counts
 * the number of commands.
 * 
 * @param t Token list.
 * 
 * @return The number of commands before encountering a boolean operator.
 */
int	count_cmds(t_token *t)
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
 * @brief Builds a pipeline structure for the current
 * execution block.
 * 
 * @param data Pointer to the data structure.
 * @param t Token list starting at the current execution block.
 * 
 * @return Filled pipeline structure, NULL if allocation fails.
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
	if (!pipe->paths)
		return (free_pipeline(pipe));
	return (pipe);
}
