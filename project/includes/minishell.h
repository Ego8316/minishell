/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:24:09 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/06 14:10:42 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//===Defines===
#ifndef MINISHELL_H
# define MINISHELL_H
# define TMP ".tmp"

//===Includes===
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"


extern int	g_last_exit_code;

//===Enums===
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

// 0 <null>, 1 cmd/arg, 2 |, 3 &, 4 ||, 5 &&, 6 <, 7 >, 8 >>, 9 <<, 10 unresolved
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
	INDELI = 9,
	UNRESOLVED_TEXT = 10,
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

typedef struct s_var
{
	t_var_type		type;
	char			*identifier;
	char			*value;
	struct s_var	*nxt;
}	t_var;

typedef struct s_parse_data
{
	char	*cmd;
	int		i;
	t_bool	expect_cmd;
	int		depth;
	t_token *tokens;
	t_var *vars;
}			t_parse_data;

typedef struct s_data
{
	char	**envp;
	char	*pwd;
	char	*oldpwd;
	t_var	*vars;
	t_token	*tokens;
}	t_data;

typedef struct s_pipeline
{
	int	n;
	int	*pipes;
	int	*pids;
}	t_pipeline;

typedef struct s_command
{
	char	*name;
	char	*pathname;
	char	*heredoc_name;
	char	**argv;
	int		fd_in;
	int		fd_out;
	int		redir_in;
	int		redir_out;
}	t_command;

//==Functions===
void	run_cmd_from_user(t_data *d);

//Parsing

t_bool	try_parse_command(char *cmd, t_data *d);

t_bool	token_make(t_token_type type, char *str, int depth, t_token **out);
t_bool	token_free_list(t_token **list);
t_bool	token_add_last(t_token_type type, char *str, int depth, t_token **list);

//Internal parsing (private)

t_bool	expand_cmd(t_parse_data *data);
t_bool	parse_operator(t_parse_data *data);
t_bool	parse_bracket(t_parse_data *data);
t_bool	parse_text(t_parse_data *data);
t_bool	parse_loop(t_parse_data *data);
t_bool	is_char_oper(char c);
t_bool	syntax_error(t_parse_data *data, int i);
char	*substitute_vars(char *str, t_var *vars);

// Signals

void	init_signal();
t_bool	has_killsig();

// Builtins

int		cd_builtin(t_data *data, char **argv);
int		echo_builtin(char **argv);
int		env_builtin(t_data *data, char **argv);
int		exit_builtin(t_data *data, char **argv);
int		export_builtin(t_data *data, char **argv);
int		pwd_builtin(t_data *data, char **argv);
int		unset_builtin(t_data *data, char **argv);

// Data

t_bool	data_init(t_data *data, char **envp);
char	**copy_envp(t_var *vars);
t_var	*var_new_node_line(char *line, t_var_type type);
int		var_add_line(t_var **vars, char *line, t_var_type type);
t_var	*var_get_line(t_var **vars, char *line);
int		var_set_line(t_var **vars, char *line);
int		is_valid_identifier(char *arg);
t_var	*var_get(t_var **vars, char *identifier);
char	*var_get_value(t_var *vars, char *identifier);
int		var_add(t_var **vars, char *identifier, char *value, t_var_type type);
int		var_set(t_var **vars, char *identifier, char *value);
int		line_get_identifier_len(char *line);
char	*line_get_value(char *line);
int		get_vars_size(t_var *vars);

// Execution

int		execute_command(t_data *data, t_token *cmds);
char	**get_paths(t_data *data);

int		get_infile(char *infile, t_token_type type, t_command *cmd, t_var *vars);
int		get_outfile(char *outfile, t_token_type type);

char	*get_heredoc_name(void);
int		get_heredoc(char *limiter, int fd, t_var *vars);

t_token	*skip_assignments(t_token *t);
int		do_assignments(t_token *t, t_var *vars);
t_command	*get_command(t_data *data, t_token *t);

// Utilities

void	*free_str(char **s);
void	*free_array(char **arr);
void	*free_vars(t_var *vars);
int		free_data(t_data *data);
void	*free_command(t_command *cmd);
void	clean_exit(t_data *data, int status);
void	swap_str(char **s1, char **s2);
int		errmsg(char *s1, char *s2, char *s3, int status);

#endif
