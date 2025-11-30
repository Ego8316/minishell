/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:46 by pkurt             #+#    #+#             */
/*   Updated: 2025/05/25 16:07:28 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character can be part of a variable name.
 *
 * Accepts alphanumeric characters, underscores, and dashes.
 *
 * @param c Character to check.
 *
 * @return TRUE if valid, FALSE otherwise.
 */
static t_bool	is_varc(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '-');
}

/**
 * @brief Appends the last exit code to the destination buffer.
 *
 * Converts the global exit code to a string and joins it, advancing the index.
 *
 * @param i Current index in the source string (advanced past '?').
 * @param new Destination string builder.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
static t_bool	substite_exit(int *i, char **new)
{
	char	*code;

	code = ft_itoa(g_last_exit_code);
	if (!code)
	{
		free(*new);
		*new = 0;
		return (FALSE);
	}
	(*i)++;
	return (strb_join(new, code));
}

/**
 * @brief Expands a variable reference found in a token string.
 *
 * Handles `$?` and standard identifiers, appending the value to the builder.
 * Leaves a literal `$` when no valid identifier follows.
 *
 * @param str Source token string.
 * @param i Current index in the string (advanced past the variable).
 * @param vars Variable list.
 * @param new Destination string builder.
 *
 * @return TRUE on success, FALSE on allocation failure.
 */
t_bool	substitute_var(char *str, int *i, t_var *vars, char **new)
{
	char	*var_name;
	char	*var_val;
	int		start;

	(*i)++;
	if (str[*i] == '?')
		return (substite_exit(i, new));
	if (!is_varc(str[*i]))
		return (strb_append(new, '$'));
	start = *i;
	while (is_varc(str[*i]))
		(*i)++;
	if (!strb_sub(str, start, (*i) - start, &var_name))
		return (FALSE);
	var_val = var_get_value(vars, var_name);
	free(var_name);
	if (!strb_join(new, var_val))
		return (FALSE);
	if (!**new)
	{
		free(*new);
		*new = 0;
	}
	return (TRUE);
}
