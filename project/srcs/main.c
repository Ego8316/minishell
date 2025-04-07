/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:01 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/04 02:12:20 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code = 0;

t_token	*test_token(char *s1, char *s2, char *s3)
{
	t_token	*arg1;
	t_token	*arg2;
	t_token	*arg3;

	arg1 = NULL;
	arg2 = NULL;
	arg3 = NULL;
	if (s1)
	{
		arg1 = malloc(sizeof(t_token));
		arg1->type = TEXT;
		arg1->str = ft_strdup(s1);
	}
	if (s2)
	{
		arg2 = malloc(sizeof(t_token));
		arg2->type = TEXT;
		arg2->str = ft_strdup(s2);
	}
	if (s3)
	{
		arg3 = malloc(sizeof(t_token));
		arg3->type = TEXT;
		arg3->str = ft_strdup(s3);
	}
	if (arg1)
		arg1->nxt = arg2;
	if (arg2)
		arg2->nxt = arg3;
	if (arg3)
		arg3->nxt = 0;
	return (arg1);
}

void	free_test(t_token *t)
{
	if (t && t->nxt && t->nxt->nxt)
	{
		free_str(&t->nxt->nxt->str);
		free(t->nxt->nxt);
	}
	if (t && t->nxt)
	{
		free_str(&t->nxt->str);
		free(t->nxt);
	}
	if (t)
	{
		free_str(&t->str);
		free(t);
	}
}

void	print_vars(t_var *vars)
{
	t_var	*v;

	v = vars;
	while (v)
	{
		printf("%s=%s\tt:%i\n", v->identifier, v->value, v->type);
		v = v->nxt;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argc;
	argv[0] = 0;
	if (!data_init(&data, envp))
		return (1);
	// int fd = open(TMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// get_heredoc("lim", fd, data.vars);
	// execute_commands(&data, test_token("salut", "ca", "va"));
	init_signal();
	char *str = read_term_line("prompt: ");
	printf ("input: %s\n", str);
/*
	int i = 0;
	while (i++ < 5 && !has_killsig())
	{
		run_cmd_from_user(&data);
	}
	*/
	free_data(&data);
	return (0);
}
