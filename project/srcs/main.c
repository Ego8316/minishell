/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:01 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 15:57:39 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*test_token(char *s1, char *s2, char *s3)
{
	t_token	*arg1;
	t_token	*arg2;
	t_token	*arg3;

	arg1 = malloc(sizeof(t_token));
	arg2 = malloc(sizeof(t_token));
	arg3 = malloc(sizeof(t_token));
	arg1->str = ft_strdup(s1);
	arg2->str = ft_strdup(s2);
	arg3->str = ft_strdup(s3);
	arg1->type = TEXT;
	arg2->type = TEXT;
	arg3->type = TEXT;
	arg1->nxt = arg2;
	arg2->nxt = arg3;
	arg3->nxt = 0;
	return (arg1);
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_token	*test;

	(void)argc;
	argv[0] = 0;
	if (!data_init(&data, envp))
		return (1);
	test = test_token("-nnnn3", "salut", "-n");
	echo_builtin(test);
	printf("\n");
	env_builtin(&data, test);
	// run_cmd_from_user();
}
*/

int	main(void)
{
	run_cmd_from_user();
}
