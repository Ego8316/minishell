/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:12:00 by ego               #+#    #+#             */
/*   Updated: 2025/04/08 14:27:48 by ego              ###   ########.fr       */
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
		return (errmsg(cmd->name, CMD_NOT_FOUND_MSG, 0, CMD_NOT_FOUND));
	free_str(&cmd->argv[0]);
	cmd->argv[0] = cmd->pathname;
	if (execve(cmd->pathname, cmd->argv, pipe->envp) == -1)
		return (errmsg_errnum(0, "execve: ", errno));
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
		return (errmsg_errnum(1, cmd->name, CMD_NOT_FOUND));
	if (access(cmd->name, F_OK | X_OK) != 0)
		return (errmsg_errnum(1, cmd->name, errno));
	if (execve(cmd->pathname, cmd->argv, pipe->envp) == -1)
		return (errmsg_errnum(0, "execve: ", errno));
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
 * @return Status code of the command, -2 if allocation fails.
 */
int	execute_command(t_data *data, t_token *t)
{
	t_cmd	*cmd;
	int		ret;
	pid_t	pid;

	cmd = get_command(data, t);
	if (!cmd || (!*cmd->argv && !do_assignments(t, data->vars)))
		return (free_command(cmd), M_ERR);
	if (!cmd->redir_in || !cmd->redir_out)
		return (free_command(cmd), 1);
	if (!*cmd->argv)
		return (free_command(cmd), 0);
	redirect_io(cmd->fd_in, cmd->fd_out);
	ret = execute_builtin(data, cmd->argv);
	if (ret != CMD_NOT_FOUND)
		return (free_command(cmd), ret);
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strchr(cmd->name, '/') && **data->pipe->envp)
			ret = execute_system_bin(data->pipe, cmd);
		else
			ret = execute_local_bin(data->pipe, cmd);
		clean_exit(data, ret);
	}
	return (free_command(cmd), wait_and_get_exit_code(pid));
}

/**
 * @brief Goes through the token list to get to the next
 * starting command.
 * 
 * @param t Token list.
 * 
 * @return Token list starting at the next command.
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
 * @brief Executes a pipeline.
 * Adds a pipeline structure to the data structure
 * for the current execution block.
 * 
 * @param data Pointer to the data structure.
 */
int	execute_pipeline(t_data *data, t_token *t)
{
	int	i;

	data->pipe = get_pipeline(data, t);
	if (!data->pipe)
		return (M_ERR);
	if (data->pipe->n == 1)
		return (execute_command(data, t));
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
			child_routine(data, t);
		t = get_to_next_command(t);
	}
	return (parent_routine(data));
}
