/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:35:52 by ego               #+#    #+#             */
/*   Updated: 2025/03/14 18:03:30 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the cd builtin:
 * No argument: cd $HOME
 * 	- if HOME not set: HOME not set
 *  - if HOME modified, still does it
 * Argument: -
 *  - goes to OLDPWD and prints it
 *  - if OLDPWD not set: OLDPWD not set
 *  More than one argument: too many arguments
 * @param data Pointer to the data structure.
 * @param args Arguments.
 * 
 * @return 0 if success, 1 otherwise.
 */
int	ct_builtin(t_data *data, t_token *args)
{
	(void)data;
	(void)args;
	return (0);
}
