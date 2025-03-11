/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:01 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 13:13:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	argv[0] = 0;
	if (!data_init(&data, envp))
		return (1);
	for (int i = 0; data.envp[i]; i++)
		printf("%s\n", data.envp[i]);
	printf(">%s\n>%s\n", data.pwd, data.oldpwd);
	// while (1)
	// 	run_cmd_from_user();
}
