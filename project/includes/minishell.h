/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:24:09 by pkurt             #+#    #+#             */
/*   Updated: 2025/04/09 15:32:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//===Defines===
#ifndef MINISHELL_H
# define MINISHELL_H

# define TMP ".tmp"
# define M_ERR -2
# define CMD_NOT_EXEC 126
# define CMD_NOT_FOUND 127
# define M_ERR_MSG "malloc: failed allocation\n"
# define IS_DIR_MSG "Is a directory"
# define CMD_NOT_FOUND_MSG "command not found"
# define COLOR_RESET "\001\033[0m\002"
# define COLOR_GREEN "\001\033[0;32m\002"
# define COLOR_BLUE  "\001\033[0;34m\002"
# define COLOR_RED   "\001\033[0;31m\002"
# define MAX_PROMPT_SIZE 1024

//===Includes===
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>


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
}	t_cmd;

typedef struct s_pipeline
{
	int		n;
	int		*pipes;
	pid_t	*pids;
	char	**paths;
	char	**envp;
	t_cmd	**cmds;
	int		stdin_backup;
	int		stdout_backup;
}	t_pipe;

typedef struct s_data
{
	char	*pwd;
	char	*oldpwd;
	t_var	*vars;
	t_token	*tokens;
	t_pipe	*pipe;
	int		line;
	char	*prefix;
}	t_data;

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

// Input

char	*read_term_line(const char* prompt);
char	*str_append_free(char *str, char c);
char	*str_remove_free(char *str, size_t count);
char	*str_new();
t_bool	isnescp(char *str, int i, char c);

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
char	*get_prefix();

// Execution

int		execute_builtin(t_data *data, char **argv);
int		execute_system_bin(t_pipe *pipe, t_cmd *cmd);
int		execute_local_bin(t_pipe *pipe, t_cmd *cmd);
int		execute_pipeline(t_data *data, t_token *t);
char	**get_paths(t_data *data);
char	*get_pathname(char *name, char **paths);

int		get_infile(char *infile, t_token_type type, t_cmd *cmd, t_data *data);
int		get_outfile(char *outfile, t_token_type type);
int		is_dir(char *pathname);

char	*get_heredoc_name(void);
int		get_heredoc(char *limiter, int fd, t_data *data);

t_token	*skip_assignments(t_token *t);
int		do_assignments(t_token *t, t_var *vars);
t_cmd	*get_command(t_data *data, t_token *t);

t_token	*get_to_next_command(t_token *t);
t_pipe	*get_pipeline(t_data *data, t_token *t);

int		get_input_redirection(t_cmd *cmd, t_token *t, t_data *data);
int		get_output_redirection(t_cmd *cmd, t_token *t);
int		redirect_io(int fd_in, int fd_out);
void	restore_standard_io(t_pipe *pipe);

void	close_pipes(t_pipe *pipe);
int		wait_and_get_exit_code(pid_t pid);
int		child_routine(t_data *data, t_cmd *cmd, int i);
int		parent_routine(t_data *data);

// Utilities

void	*free_str(char **s);
void	*free_array(char **arr);
void	*free_vars(t_var *vars);
int		free_data(t_data *data);
void	kill_all_children(t_pipe *pipe);
void	*free_command(t_cmd *cmd);
void	*free_commands(t_cmd **cmds, int n);
void	*free_pipeline(t_pipe *pipe);
void	clean_exit(t_data *data, int status);
void	swap_str(char **s1, char **s2);
int		errmsg(char *s1, char *s2, char *s3, int status);
int		errmsg_errnum(int prefix, char *s, int errnum);

#endif
