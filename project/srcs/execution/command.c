/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:46 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 02:18:25 by ego              ###   ########.fr       */
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
 * @brief Goes through the token list the get all the redirections.
 * 
 * @param cmd Current command being parsed.
 * @param t Token list.
 * @param vars Variables (for heredoc).
 * 
 * @return 1 on success, 0 on failure.
 */
int	get_input_redirection(t_command *cmd, t_token *t, t_var *vars)
{
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == REDIRIN || t->type == INDELI)
		{
			if (cmd->fd_in != -1)
				close(cmd->fd_in);
			if (cmd->heredoc_name)
			{
				unlink(cmd->heredoc_name);
				free_str(&cmd->heredoc_name);
			}
			cmd->fd_in = get_infile(t->nxt->str, t->nxt->type, cmd, vars);
			if (cmd->fd_in == -1)
				return (0);
			t = t->nxt;
		}
	}
	return (1);
}

int	get_output_redirection(t_command *cmd, t_token *t)
{
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == REDIROUT || t->type == OUTAPPEND)
		{
			cmd->fd_out = get_outfile(t->nxt->str, t->nxt->type);
			if (cmd->fd_out == -1)
				return (0);
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
t_command	*get_command(t_data *data, t_token *t)
{
	t_command *cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->pathname = NULL;
	cmd->heredoc_name = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	printf("%s\n", data->pwd);
	// get_input_redirection(cmd, t, data->vars);
	// get_output_redirection(cmd, t);
	cmd->argv = get_argv(t);
	// cmd->name = NULL;
	// if (cmd->argv[0])
	// 	cmd->name = ft_strdup(cmd->argv[0]);
	return (cmd);
}

int	execute_commands(t_data *data, t_token *cmds)
{
	t_command	*cmd;
	int			i;

	cmd = get_command(data, cmds);
	i = 0;
	while (cmd->argv[i])
	{
		printf("\t%s\n", cmd->argv[i]);
		i++;
	}
	// if (cmd->heredoc_name)
	// 	unlink(cmd->heredoc_name);
	free_command(cmd);
	return (0);
}
