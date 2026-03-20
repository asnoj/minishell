/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:28 by aronnet           #+#    #+#             */
/*   Updated: 2026/03/19 21:45:16 by aronnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== INCLUDES ========== */
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <fnmatch.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/* ========== DEFINES ========== */
# define TRUE 1
# define FALSE 0
# define ERROR_MESSAGE "ERROR during the process, Bad files"
# define ERROR_MAIN "please enter 4 args after the ./pipex"

/* ========== STATE DEFINES ========== */
# define STATE_NORMAL 10
# define STATE_IN_SINGLE_QUOTE 12
# define STATE_IN_DOUBLE_QUOTE 13

/* ========== REDIRECT DEFINES ========== */
# define REDIRECT_IN 14
# define REDIRECT_OUT 15
# define REDIRECT_APPEND 16
# define REDIRECT_HEREDOC 17
# define REDIRECT_PIPE_IN 18
# define REDIRECT_PIPE_OUT 19
# define REDIRECT_AND 20
# define REDIRECT_OR 21

extern volatile sig_atomic_t	g_signal;

/* ========== ENUMS ========== */
typedef enum e_inout
{
	OUTPUT,
	INPUT
}								t_inout;

/* ========== STRUCTURES ========== */
typedef struct s_redirect
{
	int							type;
	char						*file;
	t_list						*wild;
	int							heredoc_fd;
	struct s_redirect			*next;
}								t_redirect;

typedef struct s_token
{
	char						*command;
	char						*args;
	int							args_i;
	int							skip;
	int							pipe_fd[2];
	int							*exit_signal;
	struct s_token				*last_token;
	t_list						*env;
	t_redirect					*redirects;
	struct s_token				**head;
	struct s_token				*next;
}								t_token;

typedef struct s_token_info
{
	char						*content;
	int							was_in_single_quote;
	int							dollar_start;
	int							dollar_end;
	char						*dollar_start_ptr;
	char						*dollar_end_ptr;
}								t_token_info;

typedef struct s_tokenizer
{
	char						*line;
	int							i;
	int							state;
	char						*current_token;
	int							current_state;
	int							tok_count;
}								t_tokenizer;

/* ========== PARSING FUNCTIONS ========== */
t_tokenizer						*init_tok(char *line);
char							*add_char_to_str(char *str, char c);
t_token_info					*strs_tokenizer(char *line, t_token *token);
void							fill_all_tokens(t_tokenizer *tok,
									t_token_info *str_tokens);
void							update_state(t_tokenizer *tok, char c);
int								is_separator(char c);
int								is_quote(char c);
int								should_add_char(t_tokenizer *tok, char c);
int								is_token_end(char c, t_tokenizer *tok);
void							fill_env(t_token *token, char **envp);
int								count_tokens(char *line);
t_token_info					*expand_all_tokens(t_token_info *token_info,
									t_token *token);
void							skip_spaces(t_tokenizer *tok);
char							*expand_string(char *str, t_list *env,
									int exit_signal);
void							init_all_token_info(t_token_info *token_info);
int								is_valid_var_char(char c);
void							update_state_extand(int *state, char c);
int								is_valid_var_start(char c);

/* ========== ENV FUNCTIONS ========== */
char							*get_env_ptr(char *var_name, t_list *env);
int								get_var_name_len(char *str);
char							**transfo(t_token *token);
char							*ft_export(t_token *token);

/* ========== STRUCT INITIALIZATION FUNCTIONS ========== */
t_token							*fill_struct(t_token_info *token_info,
									char **env);
void							fill_struct_utils(t_token_info *ti,
									t_token *cur, int i, t_token **head);
t_token							*new_token(void);
t_redirect						*new_redirect(int type, char *file);
void							add_redirect(t_redirect **redir,
									t_redirect *new);
int								fill_one_token(t_token *token,
									t_token_info *token_info, int i);
int								get_redirect_type(char *str);
int								skip_redir(t_token_info *token_info, int i,
									int redirect_type, t_token *token);
int								is_operator(char *str);
void							free_all_path(char **str);
char							*expand_token_content(char *str, t_list *env,
									int exit_signal);
int								size_of(t_token_info *token_info);
int								cd_old(t_token *token);
void							free_env_list(t_list *env);
int								check_overflow(char *str);
char							*ft_export_utils(char *str);
void							apply_heredoc_pipe(t_token *token);
int								export_skip_to_space(int i, t_token *token);
int								is_numeric(char *str);
long long						ft_atoll(char *str);

/* ========== REDIRECT FUNCTIONS ========== */
char							*is_output_input(t_inout inout, t_token *token);
int								match_range(char *pattern, char *str, int i,
									int j);
int								match_set(char *pattern, char *str, int i,
									int j);
int								skip_to_bracket(char *pattern, int i);
void							add_wildcard_match(t_token *token,
									char *filename);
int								is_output_input_pipe(t_inout inout,
									t_token *token);
int								verif_end_token(t_token_info *token_info,
									int i);

/* ========== CHILD PROCESS FUNCTIONS ========== */
void							child1_process(int *pipe_fd, char *cmd,
									t_token *token, char *nametxt);
void							child2_process(int *pipe_fd, char *cmd,
									t_token *token, char *nametxt);
void							child_dup_pipe(int *pipe_fd, char *cmd,
									t_token *token);
void							fill_child(t_token *token);
void							free_all_split(char **s, int n);
int								ft_cmpt_word(char *s, char c);
int								child_set(t_token *token);
void							error_fuction(int *pipe_fd);
int								ft_fnmatch(char *pattern, char *str, int i,
									int j);
void							ft_lstadd_back(t_list **lst, t_list *new);
int								verif_and_or(t_token *token, int res);
void							clean_all_redirects(t_token *tokens);
void							rebuild_w_all(t_token *token,
									t_redirect *last_in, t_redirect *last_out);
int								ft_end_exec(t_token *token, int nb_fork1,
									int status);
void							ft_end_execu(t_token *token, int nb_fork1,
									int status);

/* ========== EXECUTION FUNCTIONS ========== */
char							**find_path(t_token *token);
char							*find_command(t_token *token);
char							*get_cmd_name(char *cmd);
void							apply_heredoc_fd(t_token *token);
char							*check_direct_path(char *cmd_name);
void							exec_cmd_with_path(t_token *token,
									char *cmd_path);
int								is_output_type(int type);
int								builtin_echo(t_token *token);
int								fast_builtin_exit(char *exit_cmd);
t_token							*init_token(t_token *token);
int								get_operator_type(t_token *token);
int								builtin_exit(t_token *token);
void							advance_past_pipes(t_token **temp);
int								ft_exec_output(t_token *temp, t_list *str);
char							*extract_word(char *str);
char							*search_in_path(char **path_dirs,
									char *cmd_name);
int								exec_cmd(t_token *token);
char							*ft_join_all(char *full_path, char **path_dirs,
									char *cmd_name, int i);
char							*free_malloc(char *str);
void							free_all(char **s);
int								ft_is_space(char c);
char							*get_first_arg(char *cmd);
int								count_args(char *cmd);
int								heredoc_cancel(char *line, int *pipefd);
int								fnmatch_crochet(char *pattern, char *str, int i,
									int j);
void							here_doc(t_token *token);
void							exec_cmd_not_found(char **av_cmd, char **envp,
									t_token *token);
int								collect_heredoc(t_token *token);
void							prepare_all_heredocs(t_token *token);
int								heredoc_finish(char *line, int *pipefd);
void							ess_pipe(t_token *token, char *line);
void							here_doc_pipe(char *LIMITEUR, char *cmd,
									t_token *token);
void							print_for_export(t_token *cmd);
int								child_set_doc(t_token *token);
void							free_during_pipe(t_token *token, char **envp,
									char **av_cmd);
int								end_linee(ssize_t bytes_read, char *buffer,
									char *LIMITEUR);
void							ft_lstadd_backk(t_list **lst, t_list *new);
int								fill_one_token(t_token *token,
									t_token_info *token_info, int i);

/* ========== BUILTIN FUNCTIONS ========== */
int								echo(t_token *token);
void							ft_env(t_token *token);
t_token							*add_redirect_type(t_token *current,
									t_token_info token_info, int *i);
int								or_and(t_token_info *token_info, int i);
int								builtin_cd(t_token *token);
int								ft_strcmp(const char *s1, const char *s2);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
char							*ft_pwd(t_token *token);
void							fill_struct_utils(t_token_info *ti,
									t_token *cur, int i, t_token **head);
int								ft_exit(t_token *token);
int								should_skip_token(int prev_type,
									int prev_status);
int								is_none(char *str);
void							sigaction_ignore(int sig);
void							cmd_env(t_token *cmd);
void							update_all_tokens_env(t_token *commands,
									t_list *env);
int								find_input_fd(t_token *token);
int								find_output_fd(t_token *token);
void							remove_duplicate_redirects(t_token *token);
int								skip_to_space(char *cmd);
t_redirect						*find_last_redirect(t_redirect *redir,
									int type1, int type2);
char							*expend_valid(t_token *token,
									t_token_info *token_info);
t_list							*ft_unset(t_token *token);
int								is_builtin_parent(char *cmd);

/* ========== UTILITY FUNCTIONS ========== */
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
int								ft_strncmpp(const char *s1, const char *s2,
									size_t n);
char							**ft_split(char *s, char c);
char							*ft_(char *s);
int								return_fd(t_token *token, t_inout inout);
char							*expend_token(char *token, char **env);
size_t							ft_strlen(const char *str);
int								is_n_flag_range(char *str, int start, int end);
void							free_redirects(t_redirect *redir);

/* ========== CLEANUP & MEMORY FUNCTIONS ========== */
void							free_token(t_token *token);
void							free_token_list(t_token *token);
void							free_redirect(t_redirect *redir);
void							free_token_info(t_token_info *info);
void							free_split(char **split);
void							free_tokens(t_token_info *tokens);
void							expand_wildcard(char *pattern, t_token *token);
void							exec_builtin(t_token *token);
int								exec_simple_cmd(t_token *token);
int								is_builtin_parent(char *cmd);
int								exec_pipeline(t_token *token);
int								verif_command(t_token *token);
int								exec_simple_here_doc(t_token *token);

/* ========== SIGNALS ========== */
void							handle_sigint(int sig);
void							handle_sigint_interactive(int sig);
void							setup_signals_interactive(void);
char							*return_path(char **str);
void							setup_signals_parent(void);
void							setup_signals_child(void);
void							handle_sigint_heredoc(int sig);
void							setup_signals_heredoc(void);
int								cd_nrml(char *str);
int								count_env(t_list *env);
char							**env_to_array(t_list *env);
void							sort_env_array(char **arr);
void							print_declare_x(char *str);
void							print_sorted_env(t_list *env);
void							pwd_actu(t_token *token);
int								is_valid_identifier(char *str);
char							*get_var_name_export(char *str);
void							export_one_var(t_token *token, char *arg);
char							*ft_export(t_token *token);
int								collect_heredoc(t_token *token);
int								is_valid_syntax(t_token_info *tokens);
char							*add_new_line(char *line);
int								collect_heredoc(t_token *token);
void							fill_all_tokens(t_tokenizer *tok,
									t_token_info *str_tokens);
int								end_of_token(char *str, int i);
void							free_one_redirect(t_redirect *redir);
char							*expand_heredoc_line(char *str, t_list *env,
									int exit_signal);
void							close_heredoc_fds(t_token *token);
int								handle_dollar(char *str, char **result,
									t_list *env, int exit_signal);
void							clean_exit(int code);

#endif