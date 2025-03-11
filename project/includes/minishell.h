/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:24:09 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 14:19:08 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//===Defines===
#ifndef MINISHELL_H
# define MINISHELL_H

//===Includes===
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//===Enums===
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

//===Structs===
typedef struct s_parse_data
{
	char	*cmd;
	int		i;
	int		depth;
	t_bool	expect_cmd;
	int		in_quotes;
}			t_parse_data;

typedef struct s_data
{
	char	**envp;
	char	*pwd;
	char	*oldpwd;
}	t_data;

//==Functions===
t_bool	parse_command(char *cmd);
void	run_cmd_from_user(void);

// Data

t_bool	data_init(t_data *data, char **envp);

// Builtins

int		env_builtin(t_data *data, char **args);

// Utilities

void	*free_array(char **arr);
int		free_data(t_data *data);
int		errmsg(char *s1, char *s2, char *s3, int status);

#endif
