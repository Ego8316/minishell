/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:01 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/23 14:05:12 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argc;
	argv[0] = 0;
	if (!data_init(&data, envp))
		return (1);
	while (1)
		run_cmd_from_user(&data);
	free_data(&data);
	return (0);
}
