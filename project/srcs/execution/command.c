/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:46 by ego               #+#    #+#             */
/*   Updated: 2025/04/01 17:21:59 by ego              ###   ########.fr       */
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
	printf("Number of commands: %i\n", get_cmds_number(cmds));
	printf("COMMAND: \"%s\"\n", cmds->str);

	if (!ft_strcmp(cmds->str, "env"))
		env_builtin(data, cmds->nxt);
	if (!ft_strcmp(cmds->str, "export"))
		export_builtin(data, cmds->nxt);
	if (is_valid_identifier(cmds->str))
		var_set_line(&data->vars, cmds->str);
	token_free_list(&data->tokens);
	return (0);
}
