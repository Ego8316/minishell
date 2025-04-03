/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:46 by ego               #+#    #+#             */
/*   Updated: 2025/04/04 00:37:13 by ego              ###   ########.fr       */
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
 * @brief Allocates memory for a command structure
 * and parses the token list to fill it.
 * 
 * @param t Token list.
 * 
 * @param Allocated field command structure, NULL
 * if allocation fails.
 */
t_command	*get_command(t_token *t)
{
	t_command *cmd;

	cmd = (t_command *)malloc(sizeof(cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = get_argv(t);
	cmd->name = NULL;
	if (cmd->argv[0])
		cmd->name = ft_strdup(cmd->argv[0]);
	return (cmd);
}

int	execute_commands(t_data *data, t_token *cmds)
{
	char	**argv;
	int		i;

	argv = get_argv(cmds);
	if (!argv)
		clean_exit(data, 0);
	i = 0;
	while (argv[i])
	{
		printf("\t%s\n", argv[i]);
		i++;
	}
	free_array(argv);
	return (0);
}
