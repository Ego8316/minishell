/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:46 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 19:27:45 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	substitute_str(char **cmd, char *val, int start, int end)
{
	int		lenc;
	int		lenv;
	char	*new;

	lenc = ft_strlen(*cmd);
	lenv = ft_strlen(val);
	new = malloc(sizeof(char) * (lenc + lenv - (end - start)));
	if (!new)
	{
		free(val);
		return (FALSE);
	}
	new[lenc + lenv - (end - start) - 1] = 0;
	ft_memcpy(new, *cmd, start - 1);
	ft_memcpy(new + (start - 1), val, lenv);
	ft_memcpy(new + (start - 1 + lenv), *cmd, lenc - end);
	//printf("val '%s'\n", val);
	//printf("val len '%i'\n", lenv);
	//printf("string '%s'\n", new);
	free(val);
	free(*cmd);
	*cmd = new;
	return (TRUE);
}

static t_bool	parse_variable(char **cmd, int *i, t_var *vars)
{
	int		start;
	int		end;
	char	*var_name;
	char	*var_val;

	start = *i;
	end = *i;
	while (ft_isalnum((*cmd)[end]) || (*cmd)[end] == '_' || (*cmd)[end] == '?')
		(end)++;
	if (start == end)
		return (TRUE);
	var_name = ft_substr(*cmd, start, end - start);
	if (!var_name)
		return (FALSE);
	var_val = var_get_value(vars, var_name);
	free(var_name);
	if (!var_val)
		return (FALSE);
	//*i += ft_strlen(var_val) - 1;
	//printf("SUBSTIUTION DATA DEBUG!\n");
	//printf("start: %i, end: %i, val: '%s'\n",start, end, var_val);
	return (substitute_str(cmd, var_val, start, end));
}

char	*substitute_vars(char *str, t_var *vars)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '$' && !parse_variable(&(str), &i, vars))
		{
			free(str);
			return (0);
		}
	return (str);
}
