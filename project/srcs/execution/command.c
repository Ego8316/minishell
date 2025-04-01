/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:46 by ego               #+#    #+#             */
/*   Updated: 2025/04/01 18:27:06 by ego              ###   ########.fr       */
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
int	get_cmds_number(t_token *cmds)
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

int	execute_commands(t_data *data, t_token *cmds)
{
	int	ret;

	ret = execute_builtin(data, cmds);
	if (ret != -1)
		return (ret);
	if (is_valid_identifier(cmds->str))
		var_set_line(&data->vars, cmds->str);
	token_free_list(&data->tokens);
	return (0);
}
