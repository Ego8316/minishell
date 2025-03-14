/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:24:09 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/14 14:21:32 by ego              ###   ########.fr       */
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

typedef enum e_var_type
{
	LOCAL = 0,
	MARKED = 1,
	ENV = 2
}	t_var_type;

//===Structs===
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	int				depth;
	struct s_token	*nxt;
}					t_token;

typedef struct s_parse_data
{
	char	*cmd;
	int		i;
	t_bool	expect_cmd;
	int		depth;
	t_token *tokens;
}			t_parse_data;

typedef struct s_var
{
	t_var_type		type;
	char			*identifier;
	char			*value;
	struct s_var	*nxt;
}	t_var;

typedef struct s_data
{
	char	**envp;
	char	*pwd;
	char	*oldpwd;
	t_var	*vars;
}	t_data;

//==Functions===
void	run_cmd_from_user(void);

//Parsing

t_bool	try_parse_command(char *cmd, t_token **out_tokens);

t_bool	token_make(t_token_type type, char *str, int depth, t_token **out);
t_bool	token_free_list(t_token **list);
t_bool	token_add_last(t_token_type type, char *str, int depth, t_token **list);

t_bool	is_char_oper(char c);
t_bool	syntax_error(t_parse_data *data, int i);

//Internal parsing (private)

t_bool	expand_cmd(t_parse_data *data);
t_bool	parse_operator(t_parse_data *data);
t_bool	parse_bracket(t_parse_data *data);
t_bool	parse_text(t_parse_data *data);
t_bool	parse_loop(t_parse_data *data);

// Builtins

int		echo_builtin(t_token *args);
int		env_builtin(t_data *data, t_token *args);
int		export_builtin(t_data *data, t_token *args);
int		pwd_builtin(t_data *data, t_token *args);

// Data

t_bool	data_init(t_data *data, char **envp);
char	**copy_envp(t_var *vars);
int		var_add_line(t_var **vars, char *line, t_var_type type);
t_var	*var_get(t_var **vars, char *line);
int		var_set(t_var **vars, char *line);
int		line_get_identifier_len(char *line);
char	*line_get_value(char *line);
t_var	*var_new_node(char *line, t_var_type type);
int		get_vars_size(t_var *vars);

// Utilities

void	*free_str(char **s);
void	*free_array(char **arr);
void	*free_vars(t_var *vars);
int		free_data(t_data *data);
void	clean_exit(t_data *data, int status);
int		errmsg(char *s1, char *s2, char *s3, int status);

#endif
