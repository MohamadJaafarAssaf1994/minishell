/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:24:12 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/17 12:28:43 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <error.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1

extern int			g_signal;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
	int				heredoc_expand;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
	int				status;
	int				prev_fd;
	int				pipe_fd[2];
}					t_cmd;

typedef struct s_shell
{
	char			**env;
	int				exit_status;
}					t_shell;

typedef struct s_expand
{
	char			*src;
	char			*dst;
	int				i;
	int				j;
	t_shell			*sh;
}					t_expand;

/*print.c*/
void				print_cmds(t_cmd *cmds);
// static	void	print_args(char **args);
// static	void	print_redirs(t_redir *redirs);
// static	void	print_redir_type(t_redir_type type);

/*signals.c*/
void				setup_signals_prompt(void);
void				setup_signals_exec(void);
void				setup_signals_child(void);
// static void 	handle_sigint_prompt(int sig);

/*builtin_pwd.c*/
int					builtin_pwd(t_cmd *cmd, t_shell *sh);

/*builtin.c*/
int					is_builtin(t_cmd *cmd);
int					is_parent_builtin(t_cmd *cmd);
int					exec_parent_builtin(t_cmd *cmds, t_shell *sh);
int					exec_builtin(t_cmd *cmds, t_shell *sh);

/*builting_cd.c*/
int					builtin_cd(t_cmd *cmd, t_shell *sh);
char				*join_key_value(char *key, char *value);
// static int		is_env_key(char *env_line, char *key);
// static	int		update_env_value(t_shell *sh, char *key, char *value);

/*builting_env.c*/
int					builtin_env(t_cmd *cmd, t_shell *sh);

/*builting_echo.c*/
int					builtin_echo(t_cmd *cmds, t_shell *sh);

/*builtin_unset.c */
// static int		remove_env_var(t_shell *sh, int index);
int					builtin_unset(t_cmd *cmds, t_shell *sh);

/*builtin_exit.c*/
int					builtin_exit(t_cmd *cmds, t_shell *sh);
// static int		is_numeric_arg(char *str);

/*builtin_export.c   */
// static void		copy_env_ptrs(char **new_env, char **old_env);
int					add_env_var(t_shell *sh, char *arg);
int					replace_env_var(t_shell *sh, int index, char *arg);
int					builtin_export(t_cmd *cmds, t_shell *sh);

/*builtin_utils.c*/
int					is_valid_identifier(char *str);
int					env_size(char **env);
int					get_env_index(char **env, char *arg);

/*utils.c*/
void				free_redirs(t_redir *redirs);
void				free_cmds(t_cmd *cmds);
void				free_tab(char **tab);
void				cleanup_shell(t_shell *sh);

/*tmp_parse.c*/
int					is_pipe_token(char *s);
int					is_redir_token(char *s);
t_redir_type		get_redir_type(char *s);
t_redir				*create_redir(t_redir_type type, char *file);
void				add_redir_back(t_redir **redirs, t_redir *new_redir);

/*tmp_parse_suite.c*/
// static int		count_args_until_pipe(char **tokens, int start);
// static int		fill_cmd_until_pipe(t_cmd *cmd, char **tokens, int *i);
void				add_cmd_back(t_cmd **cmds, t_cmd *new_cmd);
t_cmd				*create_cmd_from_tokens(char **tokens, int *i);
t_cmd				*parse_line(char *line, int *status);

/*copy_env.c*/
char				**copy_env(char **env);
int					init_shell(t_shell *sh, char **env);

/*expansion.c*/
int					is_quote(char c);
int					has_quotes(char *word);
int					is_name_start(char c);
int					is_name_char(char c);
char				*env_value_span(char **env, char *word, int start, int len);
void				init_expand(t_expand *ex, char *src, char *dst,
						t_shell *sh);
int					variable_len(char *word, int *i, t_shell *sh);
int					expanded_len(char *word, t_shell *sh, int allow_vars);
int					heredoc_len(char *line, t_shell *sh);
int					copy_variable(t_expand *ex);
int					copy_expanded(char *dst, char *word, t_shell *sh,
						int allow_vars);
char				*expand_word(char *word, t_shell *sh, int allow_vars);
int					expand_commands(t_cmd *cmds, t_shell *sh);
char				*expand_heredoc_line(char *line, t_shell *sh);

/*shell_loop.c*/
void				shell_loop(t_shell *sh);
int					execute(t_cmd *cmds, t_shell *sh);

/*tokenizer.c*/
int					is_blank(char c);
int					is_operator(char c);
int					operator_len(char *line, int i);
int					word_end(char *line, int start);
int					next_token_end(char *line, int i);
char				**shell_tokenize(char *line);

/*heredoc.c*/
// static int		fill_heredoc_pipe(int write_fd, char *delimiter);
// static int		prepare_one_heredoc(t_redir *redir, t_shell *sh);
void				heredoc_child_loop(int pipe_fd[2], t_redir *redir,
						t_shell *sh, t_cmd *cmds);

/*heredoc2.c*/
int					fill_heredoc_pipe(int pipe_fd[2], t_redir *redir,
						t_shell *sh, t_cmd *cmds);
int					prepare_one_heredoc(t_redir *redir, t_shell *sh,
						t_cmd *cmds);
int					prepare_heredocs(t_cmd *cmds, t_shell *sh);
void				close_other_heredocs(t_cmd *cmds, t_cmd *skip);

/*exec_utils_1.c */
int					get_exit_status(int status);
char				*get_cmd_path(char *cmd, char **env);
char				*get_env_value(char **env, char *key);
// static char		*find_path(char **paths, char *cmd);
// static char		*join_path_cmd(char *dir, char *cmd);

/*pipeline.c*/
void				exec_shell_script(char *path, char **args, char **env);
int					exec_pipeline(t_cmd *cmds, t_shell *sh);
void				exec_child(t_cmd *cmd, t_cmd *cmds, t_shell *sh);
void				ft_close(t_cmd *cmd);

/*redirections.c*/
// static int		dup_redirection(t_redir *redir, int fd);
// static int		open_redirection(t_redir *redir);
int					apply_redirections(t_cmd *cmd);

/*parent_builtin_redirs.c*/
int					exec_parent_builtin_with_redir(t_cmd *cmd, t_shell *sh);

/*exec_utils_2.c*/
void				close_pipe(int pipe_fd[2]);
int					create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2]);
void				setup_child_pipes(int prev_fd, int pipe_fd[2], t_cmd *cmd);
pid_t				fork_pipeline_child(t_cmd *cmd, t_cmd *cmds, t_shell *sh,
						int pipe_fd[2]);
#endif
