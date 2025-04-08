/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:58:29 by ego               #+#    #+#             */
/*   Updated: 2025/04/07 23:57:56 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Given a process' pid, waits for its termination
 * (whether it exited or was ended by signal) and returns
 * its exit code.
 * 
 * @param pid Process' pid to be waited.
 * 
 * @return Process' exit code.
 */
int	wait_and_get_exit_code(pid_t pid)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(pid, &status, 0);
	if (wpid == pid && WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (wpid == pid && WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

/**
 * @brief 
 * 
 * - if builtin: execute it
 * - if not, check if directory (if so exit 126)
 * - if not, check if extern command (if so execute it)
 * - if not, exit 127
 * 
 * @param data Pointer to the data structure.
 * @param t Token list starting at the child's command.
 */
void	child_routine(t_data *data, t_token *t)
{
	t_cmd	*cmd;

	cmd = get_command(data, t);
	if (!cmd)
		exit (M_ERR);
	execute_builtin(data, cmd->argv);
}

/**
 * @brief Waits for each child routine to end.
 * 
 * @param data Pointer to the data structure.
 * 
 * @return Exit code of the last child.
 */
int		parent_routine(t_data *data)
{
	int		i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (i < data->pipe->n)
	{
		exit_code = wait_and_get_exit_code(data->pipe->pids[i]);
		if (exit_code == M_ERR)
			return (free_pipeline(data->pipe), M_ERR);
		i++;
	}
	return (exit_code);
}
