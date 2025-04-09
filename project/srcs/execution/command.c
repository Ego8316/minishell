/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:46 by ego               #+#    #+#             */
/*   Updated: 2025/04/09 13:59:37 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of arguments for
 * the given command.
 * 
 * @param t Token list.
 * 
 * @return Argument count.
 */
int	get_argc(t_token *t)
{
	int	argc;

	argc = 0;
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == TEXT)
			argc++;
		if (t->type >= REDIRIN && t->type <= INDELI)
			t = t->nxt;
		t = t->nxt;
	}
	return (argc);
}

/**
 * @brief Allocates memory for an array of strings
 * and duplicates each argument into that array.
 * 
 * @param tokens Token list.
 * 
 * @return Allocated array of strings, NULL if
 * allocation fails.
 */
char	**get_argv(t_token *t)
{
	int		i;
	char	**argv;

	i = 0;
	argv = (char **)malloc((get_argc(t) + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == TEXT)
		{
			argv[i] = ft_strdup(t->str);
			if (!argv[i])
				return (free_array(argv));
			i++;
		}
		if (t->type >= REDIRIN && t->type <= INDELI)
			t = t->nxt;
		t = t->nxt;
	}
	argv[i] = 0;
	return (argv);
}

/**
 * @brief Gets the command redirections and stops at the first that fails.
 * 
 * @param cmd Current command structure.
 * @param t Token list.
 * @param data Pointer to the data structure.
 * 
 * @return 1 on success, 0 if a redirection fails and -2 if allocation fails.
 */
static int	get_command_redirections(t_cmd *cmd, t_token *t, t_data *data)
{
	cmd->redir_in = 1;
	cmd->redir_out = 1;
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == REDIRIN || t->type == INDELI)
		{
			cmd->redir_in = get_input_redirection(cmd, t, data);
			if (cmd->redir_in != 1)
				return (cmd->redir_in);
			t = t->nxt;
		}
		if (t->type == REDIROUT || t->type == OUTAPPEND)
		{
			cmd->redir_out = get_output_redirection(cmd, t);
			if (cmd->redir_out != 1)
				return (cmd->redir_out);
			t = t->nxt;
		}
		t = t->nxt;
	}
	return (1);
}

/**
 * @brief Allocates memory for a command structure
 * and parses the token list to fill it.
 * 
 * @param data Pointer to the data structure.
 * @param t Token list.
 * 
 * @param Allocated filled command structure, NULL
 * if allocation fails.
 */
t_cmd	*get_command(t_data *data, t_token *t)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->pathname = NULL;
	cmd->heredoc_name = NULL;
	cmd->argv = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	if (get_command_redirections(cmd, t, data) == M_ERR)
		return (free_command(cmd), NULL);
	cmd->argv = get_argv(skip_assignments(t));
	if (cmd->argv && cmd->argv[0])
		cmd->name = ft_strdup(cmd->argv[0]);
	if (!cmd->argv || (cmd->argv[0] && !cmd->name) || cmd->redir_in == M_ERR)
		return (free_command(cmd));
	return (cmd);
}
