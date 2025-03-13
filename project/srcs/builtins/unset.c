/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:40 by ego               #+#    #+#             */
/*   Updated: 2025/03/13 03:08:21 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the unset builtin: removes
 * the value for each found identifier. Does
 * nothing for unfound identifier. If the
 * identifier corresponds to an environment
 * variable, also removes it from envp.
 * 
 * @return 0 for success.
 */
int	unset_builtin(t_data *data, t_token *args)
{
	t_var	*v;

	if (!args)
		return (0);
	while (args && args->type == TEXT)
	{
		v = data->vars;
		while (v)
		{
			if (!ft_strcmp(v->identifier, args->str))
			{
				if (v->type == ENV)
					return (0); // Here should remove from envp
				free(v->value);
				v->value = ft_strdup("");
				v->type = LOCAL;
			}
			v = v->nxt;
		}
		args = args->nxt;
	}
	return (0);
}
