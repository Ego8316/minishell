/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:24:09 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/11 19:59:02 by pkurt            ###   ########.fr       */
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

// 0 <null>, 1 resolved cmd/arg, 2 |, 3 &, 4 ||, 5 &&, 6 <, 7 >, 8 >>, 9 <<
typedef enum e_token_type
{
	UNDETERMINED = 0,
	TEXT = 1,
	PIPE = 2,
	BGEXEC = 3,
	OROPER = 4,
	ANDOPER = 5,
	REDIRIN = 6,
	REDIROUT = 7,
	OUTAPPEND = 8,
	INDELI = 9
}	t_token_type;


//===Structs===
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*nxt;
}					t_token;

typedef struct s_parse_data
{
	char	*cmd;
	int		i;
	t_bool	expect_cmd;
	char	*arg;
	t_token *tokens;
}			t_parse_data;

typedef struct s_data
{
	char	**envp;
	char	*pwd;
	char	*oldpwd;
}	t_data;

//==Functions===
void	run_cmd_from_user(void);

//Parsing

t_bool	try_parse_command(char *cmd, t_token **out_tokens);

t_bool	token_make(t_token_type type, char *str, t_token **out);
t_bool	token_free_list(t_token **list);
t_bool	token_add_last(t_token_type type, char *str, t_token **list);

t_bool	parse_pipe(t_parse_data *data);
t_bool	parse_redirection(t_parse_data *data);

// Data

t_bool	data_init(t_data *data, char **envp);

// Builtins

int		env_builtin(t_data *data, char **args);
int		pwd_builtin(t_data *data, char **args);

// Utilities

void	*free_array(char **arr);
int		free_data(t_data *data);
int		errmsg(char *s1, char *s2, char *s3, int status);

#endif
