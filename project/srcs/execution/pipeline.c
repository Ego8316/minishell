/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:53:15 by ego               #+#    #+#             */
/*   Updated: 2025/04/03 21:16:03 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * @brief Executes a pipeline.
 * 	- Counts the number of commands.
 * 	- Creates all pipes required.
 */
int execute_pipeline(t_data *data, t_token *cmds)
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
