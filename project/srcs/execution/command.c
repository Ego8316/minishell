/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:46 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 15:25:29 by ego              ###   ########.fr       */
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
			printf("argv %i : %s\n", i, t->str);
			argv[i] = ft_strdup(t->str);
			printf(">>%s\n", argv[i]);
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
 * @brief Goes through the token list the get all the input redirections.
 * When encountering a new redirection, closes the previously opened one
 * if needed. If previous one was a heredoc, deletes the corresponding
 * temporary file and frees the heredoc_name string.
 * 
 * @param cmd Current command being parsed.
 * @param t Token list.
 * @param vars Variables (for heredoc).
 * 
 * @return 1 on success, 0 on failure, -1 if allocation fails.
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
			cmd->fd_in = get_infile(t->nxt->str, t->type, cmd, vars);
			if (cmd->fd_in == -2)
				return (-1);
			if (cmd->fd_in == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(t->nxt->str);
				return (0);
			}
			t = t->nxt;
		}
		t = t->nxt;
	}
	return (1);
}

/**
 * @brief Goes through the token list the get all the output redirections.
 * When encountering a new redirection, closes the previously opened one
 * if needed.
 * 
 * @param cmd Current command being parsed.
 * @param t Token list.
 * 
 * @return 1 on success, 0 on failure.
 */
int	get_output_redirection(t_command *cmd, t_token *t)
{
	while (t && t->type != PIPE && t->type != ANDOPER && t->type != OROPER)
	{
		if (t->type == REDIROUT || t->type == OUTAPPEND)
		{
			if (cmd->fd_out != -1)
				close(cmd->fd_out);
			cmd->fd_out = get_outfile(t->nxt->str, t->type);
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
	get_input_redirection(cmd, t, data->vars);
	get_output_redirection(cmd, t);
	cmd->argv = get_argv(skip_assignments(t));
	cmd->name = NULL;
	if (cmd->argv[0])
		cmd->name = ft_strdup(cmd->argv[0]);
	return (cmd);
}

int	execute_commands(t_data *data, t_token *cmds)
{
	t_command	*cmd;
	int			i;

	cmd = get_command(data, cmds);
	do_assignments(cmds, data->vars);
	i = 0;
	while (cmd->argv[i])
	{
		printf("\t%s\n", cmd->argv[i]);
		i++;
	}
	free_command(cmd);
	return (0);
}
