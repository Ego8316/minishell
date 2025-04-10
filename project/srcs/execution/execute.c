/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:12:00 by ego               #+#    #+#             */
/*   Updated: 2025/04/10 18:40:18 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Simple switch to handle builtins.
 * 
 * @param data Pointer to the data structure.
 * @param argv Command's argv.
 * 
 * @return Whatever the builtin returns, 127 if the command
 * is not a builtin, -2 if allocation fails (for export).
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
	return (CMD_NOT_FOUND);
}

/**
 * @brief Executes a system binary if it can be found
 * in the PATH.
 * 
 * @param pipe Pointer to the pipe structure.
 * @param cmd Current command.
 * 
 * @return 127 if pathname cannot be found (either command not found
 * or PATH not set or empty), -2 if allocation fails, whatever execve
 * returns if it fails.
 */
int	execute_system_bin(t_pipe *pipe, t_cmd *cmd)
{
	cmd->pathname = get_pathname(cmd->name, pipe->paths);
	if (!cmd->pathname)
		return (M_ERR);
	if (!*cmd->pathname)
		return (errmsg_errnum(0, cmd->name, CMD_NOT_FOUND));
	if (execve(cmd->pathname, cmd->argv, pipe->envp) == -1)
		return (errmsg_errnum(0, "execve", errno));
	return (1);
}

/**
 * @brief Tries and execute the command as is.
 * 
 * @param pipe Pointer to the pipe structure.
 * @param cmd Current command.
 * 
 * @return
 */
int	execute_local_bin(t_pipe *pipe, t_cmd *cmd)
{
	if (is_dir(cmd->name))
		return (errmsg_errnum(1, cmd->name, CMD_NOT_EXEC));
	if (access(cmd->name, F_OK) != 0)
		return (errmsg_errnum(1, cmd->name, errno));
	if (access(cmd->name, F_OK | X_OK) != 0)
		return (errmsg_errnum(1, cmd->name, errno));
	if (execve(cmd->name, cmd->argv, pipe->envp) == -1)
		return (errmsg_errnum(0, "execve", errno));
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
 * @param cmd Single command to execute.
 * 
 * @return Exit code of the command, -2 if allocation fails.
 */
static int	execute_command(t_data *data, t_token *t, t_cmd *cmd)
{
	int		ret;
	pid_t	pid;

	if (!*cmd->argv && !do_assignments(t, &data->vars))
		return (M_ERR);
	if (!cmd->redir_in || !cmd->redir_out)
		return (1);
	if (!*cmd->argv)
		return (0);
	redirect_io(cmd->fd_in, cmd->fd_out);
	ret = execute_builtin(data, cmd->argv);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strchr(cmd->name, '/') && *data->pipe->paths)
			ret = execute_system_bin(data->pipe, cmd);
		else
			ret = execute_local_bin(data->pipe, cmd);
		clean_exit(data, ret);
	}
	return (wait_and_get_exit_code(pid));
}

/**
 * @brief Executes a pipeline.
 * Adds a pipeline structure to the data structure
 * for the current execution block.
 * 
 * @param data Pointer to the data structure.
 * @param t Token list starting at the current execution block.
 * 
 * @return 1 on failure (if a fork failed for instance), -2 if
 * allocation fails, exit code of the last child otherwise.
 */
int	execute_pipeline(t_data *data, t_token *t)
{
	int	i;

	data->pipe = get_pipeline(data, t);
	if (!data->pipe)
		return (M_ERR);
	if (data->pipe->n == 1)
		return (execute_command(data, t, data->pipe->cmds[0]));
	i = -1;
	while (++i < data->pipe->n)
	{
		data->pipe->pids[i] = fork();
		if (data->pipe->pids[i] == -1)
		{
			perror("minishell: fork");
			return (free_pipeline(data->pipe), 1);
		}
		else if (data->pipe->pids[i] == 0)
			clean_exit(data, child_routine(data, data->pipe->cmds[i], i));
		t = get_to_next_command(t);
	}
	return (parent_routine(data));
}
