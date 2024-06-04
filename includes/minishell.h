/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 05:16:40 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 06:48:52 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# define PATH_MAX 1024

typedef enum s_exit
{
	FALSE,
	TRUE,
}					t_exit;

typedef struct s_data
{
	int				exit_status;
	pid_t			*g_pid;
	int				signal;
}					t_g_lb_data;

extern t_g_lb_data	g_lb_data;

typedef enum s_builtin
{
	ECHO = 1,
	CD,
	ENV,
	PWD,
	UNSET,
	EXIT,
	EXPORT,
	NOT_BUILTIN,
}					t_builtin;

typedef struct s_redir
{
	char			*file_out;
	char			type;
	char			*centent;
	int				pipefd[2];
}					t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_expand_data
{
	int				idx;
	char			*new_str;
	bool			double_quotes;
	char			*var_name;
	char			*holder;
	t_env			*env;
}					t_expand_data;

typedef struct s_add_special
{
	char			*new_str;
	int				idx;
	bool			trigger;
	bool			single_quotes;
	bool			double_quotes;
}					t_add_special;

typedef struct s_commands
{
	pid_t			pid;
	int				commands_count;
	char			*command;
	char			**arg;
	char			*path;
	int				exit_status;
	int				execute_status;
	char			**environment;
	int				redir_count;

	t_env			*env_list;
	t_redir			*redir;
	bool			should_expand_heredoc;
}					t_commands;

//Tools funcs
extern void			rl_replace_line(const char *str, int x);
size_t				str2d_len(char **str);
void				free_2d(char **str);
char				*ft_str3join(char *s1, char *s2, char *s3);
bool				print_err(char *str);
void				escape_string(const char *input, int *idx);
char				**split_pipe(char *str, char c);
char				*get_first_word(char *str);
void				append_command(t_commands **lst, char *typed_command);
void				display_commands(t_commands *lst);
char				*reduce_string(char *str);
size_t				count_len_with_one_space(char *str);
void				free_linked_commands(t_commands *lst);
char				*join_splite(char **splited_str, int idx);
void				init_commands(t_commands *commands, size_t count);
void				free_commands(t_commands *commands);
void				print_commands(t_commands *commands);
void				trim_commands(char **commands);
char				*join_commands(char **str);
void				remove_middle_quotes(t_commands *commands);
char				*append_str(char *str, char c);
char				*append_str_begining(char *str, char c);
void				remove_quotes(t_commands *commands);
void				clear_commands(t_commands *commands);
char				**join_arr(char **arr, char *new);
char				**get_args(char *str, int arr_idx);
char				**remove_first_pos_2d_arr(char **str);
char				*get_substr(char *str, int start, int end);
char				*expand(char *str, t_env *env, bool single_quotes,
						bool double_quotes);
void				quotes_switcher(bool *single_quotes, bool *double_quotes,
						bool single_case, bool double_case);
bool				redir_check(char *str);
void				handle_redirection(t_commands *commands, char *str,
						char *help);
char				*put_char_in_pos(char *str, int c, int pos);
char				*join_double_pointer(char **splited);
int					ft_strcmp(char *s1, char *s2);
int					is_number(char str);
int					is_alpha(char str);
void				fixing_expand(t_commands *commands);
void				init_expand(t_commands *commands, t_env *env);
bool				first_condition(char *str, int idx, bool single_quotes);
bool				second_condition(char *str, int idx);
bool				third_condition(char *str, int idx);
void				expand_case(char *str, int *idx, char *var_name);
void				should_expand_her(t_commands *commands);
void				handling_empty_quotes(t_commands *commands);

char				*get_var_name(char *str);
int					get_char_pos(char *str, char c);
char				*get_var(char *str, char **env);
void				exit_state(char **new_str);
char				*trim_value(char *str);
void				expand_init(t_expand_data *data, t_env *env);
void				expand_second(char **var_name, t_env *env, char **holder,
						char **new_str);
void				expand_handle_dollar_dollar(t_expand_data *data);
void				expand_first_condition(t_expand_data *data, char **str,
						t_env *env);
void				escape_chars(char *str, int *i, char c);
void				escape_chars(char *str, int *i, char c);
void				init_vars(size_t *counter, bool *double_quotes,
						bool *single_quotes, bool *trigger);
void				count_redir_for_alloc_comp(char *str, int *idx, char c,
						int *count);
char				get_redir_type(char *str);
bool				check_if_redir(char *str);
void				init_redir(t_redir *redirs, int count);
size_t				count_redirs(char **splited);
int					count_redir_for_alloc(char *str, bool double_quotes,
						bool single_quotes);
void				handle_quotes(t_commands *commands);
void				add_space_comp(char **new_str, int *idx, char *to_join,
						int to_increment);
void				add_special_char_comp(bool *trigger, char **new_str,
						char *to_join);
void				init_add_special_char(t_add_special *data);
void				handle_redirection_con(t_commands *commands,
						char **splited);
void				handle_redirection_con_tree(t_commands *commands,
						char **holder, int *idx2);
void				handle_redirection_con_two(t_commands *commands,
						char **holder, int redir_idx);
char				*add_special_char(char *str);
void				handle_redirection_con_two(t_commands *commands,
						char **holder, int redir_idx);
void				add_special_char_comp_two(char *str, t_add_special *data);
bool				check_quotes(const char *input);
bool				check_redirection_position(const char *input);
bool				check_1d_err_comp(const char *input);
bool				check_sequensial_redirs(const char *input, char c,
						bool single_quote, bool double_quote);

bool				last_redir_check(const char *str, bool single_quotes,
						bool double_quotes, int idx);

//Errors funcs--------------------------------------------------------
unsigned int		count_appearance(const char *str, char c);
bool				check_user_input(const char *input);
void				release_mem(void *para1, void *para2, void *para3,
						void *para4);
bool				check_1d_err(const char *input);

// PARSING FUNCTION:----------------------------------------------------
t_commands			*parse(const char *input, t_env *env, char **env_arr);

//BUILTIN FUNCTION : ----------------------------------------------------
void				wait_for_children(t_commands *cmd);
void				handle_invalid_key(char *arg);
void				export_argument(char *arg, t_env **env_list);
int					check_if_key_exist_and_update(t_env *env_list, char *key);
void				close_child_pipe_fds(t_commands *cmd, int **fd,
						int num_commands);
void				parent_process(t_commands *cmd, int **fd, int num);
int					check_is_builtin(t_commands *cmd);
void				export_cmd(t_commands *cmd, t_env *env_list);
void				unset_cmd(t_commands *cmd, t_env *env_list);
void				env_cmd(t_env *head, t_commands *cmd);
void				pwd_cmd(void);
void				exit_cmd(t_commands *cmd);
void				exit_cmd(t_commands *cmd);
void				echo_cmd(t_commands *command);
void				cd_cmd(t_commands *command, t_env *env);
t_env				*add_node(t_env *env_list, char *key, char *value);

//-----------------------------------------------------------------------
//EXECUTION FUNCTION :----------------------------------------------------
int					prepare_cmd(t_commands *cmd, char *path);
void				handle_error_forking(t_commands *cmd);
void				createpipes(t_commands *cmd, int *index);
bool				is_valid_key(const char *arg);
t_env				*update_existing_key(t_env *env_list, char *key,
						char *value);
t_env				*add_new_key(t_env *env_list, char *key, char *value);
void				extract_key_value(char *arg, char **key, char **value);
t_env				*modify_value(t_env *env_list, char *key, char *value);
t_env				*add_node(t_env *env_list, char *key, char *value);
int					check_is_path_exist(t_env *head);
void				write_on_pipe(t_commands *cmd, char *content_herdoc,
						int *index, t_env *env);
void				get_status_value(int *status, t_commands *cmd, int *index);
void				childp(char **line, t_commands *cmd, char *del);
void				handle_pipes(t_commands *cmd, int *index,
						char *content_herdoc);

void				execute_bin_cmd(t_commands *cmd, t_env *env_list);
void				execute(t_commands *cmd, t_env *data);
void				handle_multipe_command(t_commands *cmds, t_env *env_list);
void				execute_multipe_cmd(t_commands *cmd, t_env *env_list);
void				execute_command_single(t_commands *cmd, t_env *env_list);
void				execute_bin_cmd(t_commands *cmd, t_env *env_list);
void				execute_builtin(t_commands *cmd, t_env *env_list);
//  void execute_single_cmd(t_commands *cmd,  t_env *env_list);

//help function:--------------------------------------------------------------
void				copy_env(char **envp, t_env **head, int i);
void				free_str(char **str);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strcat(char *dest, char *src);
char				*find_cmd_path(t_commands *cmd, char *path_env);
char				*find_path(t_env *env_list, char *path_search);

//----------------------------------------------------------------------------

// REDIRECTION FUNCTION :-----------------------------------------------------
int					execute_command(t_commands *cmd, t_env *env_list);
void				add_declare_to_env(t_env *env_list);
int					is_number(char str);
int					is_alpha(char str);
int					open_output_file(t_commands *cmd, int pos);
int					handle_output_file(t_commands *cmd, int *fd_in, int pos);
int					handle_input_file(t_commands *cmd, int *fd_in, int pos);
void				check_type_of_redirection(t_commands *cmd, int *fd);
int					handle_input_heredoc(t_commands *cmd, int index, char *del,
						t_env *env);
void				herdoc(t_commands *cmd, t_env *env);
void				sigint_handler_child(int signum);
void				handle_parent_signals(void);
void				handle_sigint(int sig);
void				handle_child_signals(int sig);
char				*my_strjoin(char *s1, char *s2);

void				print_errors(char *cmd, char *arg, char *message);
void				writepipe(t_commands *cmd, int *index, t_env *env);
//----------------------------------------------------------------------------

#endif
