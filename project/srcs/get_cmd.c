/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:54:41 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 18:21:22 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets and runs a command from user.
 */

void	run_cmd_from_user(void)
{
	t_token *tokens;

	if (try_parse_command(readline("[minishell]: "), &tokens))
		token_free_list(&tokens);
}
