/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:12:28 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:33:03 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"

# define PROMPT "\001\e[38;2;162;156;187m\002👾​Minishell👾​ => \001\e[0m\002"
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define SUCCESS 0
# define FAILURE 1
# define SYNTAX  2

// The one and only global variable 😎​
extern int	g_last_exit_code;

// Structures
typedef struct s_token
{
	char			*str;
	char			*str_save;
	bool			var_exists;
	int				type;
	int				status;
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;
typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_limit;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_save;
	int		stdout_save;
}	t_io_fds;
typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	bool		interactive;
	bool		syntax_error;
	t_token		*token;
	char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
}	t_data;

// enum
enum e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

// BASE
// free.c
void		cleanup_shell_data(t_data *data, bool clear_history);
void		cleanup_file_descriptors(t_command *cmds, bool close_backups);
void		cleanup_io_structure(t_io_fds *io);
void		cleanup_pointer(void *ptr);
void		cleanup_string_array(char **tab);

//init_data.c
bool		initialize_shell_data(t_data *data, char **env);
void		setup_io_structure(t_command *cmd);

// BUILTINS_CMDS
int			builtin_environment_display(t_data *data, char **args);
int			builtin_print_working_directory(t_data *data, char **args);
int			builtin_echo_command(t_data *data, char **args);
int			builtin_export_variable(t_data *data, char **args);
int			builtin_remove_variable(t_data *data, char **args);
int			builtin_change_directory(t_data *data, char **args);
int			builtin_exit_shell(t_data *data, char **args);

// ENVIRONMENT
// env_core.c
char		**ft_reallocate_env_array(t_data *shell_data, int new_size);
char		*ft_create_env_value_string(char *value);
int			ft_find_environment_variable_index(char **env, char *var);
char		*ft_extract_environment_variable_value(char **env, char *var);

// env_edit.c
bool		ft_set_environment_variable(t_data *data, char *key, char *value);
bool		ft_remove_environment_variable(t_data *data, int idx);

// env_utils.c
char		*ft_create_search_pattern(char *variable_name);
int			ft_count_environment_variables(char **env);
bool		ft_validate_environment_variable_key(char *var);

// ERROR
// exit.c
void		terminate_shell(t_data *data, int exno);

// error_management.c
int			print_command_error(char *command,
				char *detail, char *error_message,
				int error_nb);
void		print_syntax_error(char *errmsg, char *detail, int quotes);
bool		display_usage(bool return_value);

// EXEC
// exec.c
int			ft_execute_command_pipeline(t_data *data);

// cmd_exec.c
int			exec_cmd(t_data *data, t_command *cmd);
int			run_builtin(t_data *data, t_command *cmd);

// utils.c
bool		is_dir(char *cmd);
int			check_cmd_valid(t_data *data, t_command *cmd);

// path_management.c
char		*ft_resolve_command_path(t_data *data, char *cmd);

// EXPANSION

//var_checker.c
bool		should_expand_var(t_token *temp, int i);
bool		should_expand_heredoc_var(char *str, int i);

//var_finder.c
char		*extract_variable_name(char *str);
int			calculate_variable_name_length(char *str);
bool		check_variable_character_validity(char c);

//replace_var.c
int			replace_var(t_token **token_node, char *var_value, int index);
void		copy_var_value(char *new_str, char *var_value, int *j);
char		*expand_heredoc_variables(t_data *data, char *str);
char		*replace_str_heredoc(char *str, char *var_value, int index);

// expand_utils.c
void		copy_var_value(char *new_str, char *var_value, int *j);
char		*get_new_token_string(char *oldstr, char *var_value,
				int newstr_size, int index);

//handle_quotes.c
int			handle_token_quote_removal(t_data *data);
bool		has_quotation_marks(char *str);
int			unq_len(char *str, int count, int i);

//delete_quotes.c
int			strip_quotes_from_token(t_token **token_node);

//expand_var.c
bool		check_next_separator(char c);
bool		check_var_in_quotes(char *str, int i);
int			expand_variables(t_data *data, t_token **token_lst);

//value_recovery.c
char		*retrieve_variable_value(t_token *token, char *str, t_data *data);

// LEXER
// tokenize.c
int			parse_input_string(t_data *data, char *str);

// tokenize_utils.c
int			process_token_element(int *i, char *str, int start, t_data *data);
int			update_quote_status(int status, char *str, int i);
int			identify_token_type(char *str, int i);
int			extract_word_token(t_token **token_lst, char *str,
				int index, int start);
int			store_operator_token(t_token **token_lst, char *str,
				int index, int type);

// lexer_syntax.c
int			validate_token_sequence(t_token **token_lst);

// var_checker.c
int			process_token_variables(t_token **token_lst);

// token_utils.c
t_token		*make_token(char *content, char *backup_content,
				int token_type, int token_status);
void		add_token_to_end(t_token **head_ref, t_token *node_to_add);
void		delete_token_node(t_token *node_to_delete,
				void (*deletion_func)(void *));
void		free_entire_token_list(t_token **head_ref,
				void (*deletion_func)(void *));
t_token		*substitute_node_with_chain(t_token **list_head,
				t_token *old_node, t_token *new_chain);

// user_input_parsing.c
bool		process_command_line(t_data *data);

// PARSING
// new_cmd.c
void		build_command_structures(t_data *data, t_token *token);

// default_args.c
int			calculate_word_tokens(t_token *temp);
int			populate_command_arguments(t_token **token_node,
				t_command *last_cmd);
int			extend_standard_arguments(t_token **token_node,
				t_command *last_cmd);
int			initialize_standard_arguments(t_token **token_node,
				t_command *last_cmd);

// echo_args.c
int			extend_echo_arguments(t_token **token_node, t_command *last_cmd);
int			initialize_echo_arguments(t_token **token_node,
				t_command *last_cmd);

// echo_utils.c
char		*concatenate_variable_tokens(t_token **token_node);
int			calculate_expanded_args(t_token *scanner);
char		**duplicate_args_with_expansion(int len, char **new_tab,
				t_command *last_cmd, t_token *processor);
void		filter_empty_variable_args(t_token **tokens);

// cmd_list.c
t_command	*create_new_command_node(bool pipe_flag);
void		append_command_to_list(t_command **command_head,
				t_command *new_command);
t_command	*get_last_command_node(t_command *cmd);

// free_cmd_list.c
void		free_single_command(t_command *cmd_node,
				void (*deallocator)(void *));
void		destroy_command_list(t_command **command_list,
				void (*deallocator)(void *));

// parsing
void		process_output_redirection(t_command **last_cmd,
				t_token **token_lst);
char		*build_file_path(char *file_to_open);
bool		clear_existing_file_reference(t_io_fds *io, bool input_mode);
void		process_input_token(t_command **last_cmd, t_token **token_lst);
void		handle_append_redirection(t_command **last_cmd,
				t_token **token_lst);
void		handle_heredoc_redirection(t_data *data, t_command **last_cmd,
				t_token **token_lst);
bool		process_heredoc_input(t_data *data, t_io_fds *io, int fd);
void		handle_pipeline_connection(t_command **cmd, t_token **token_lst);
void		handle_word_tokens(t_command **cmd, t_token **token_lst);
bool		create_heredoc_file(t_data *data, t_io_fds *io);
bool		is_syntax_error(t_token *tokens);

// SYSTEM
// pipes.c
bool		initialize_command_pipes(t_data *data);
bool		configure_pipe_redirections(t_command *cmds, t_command *curr_cmd);
void		cleanup_unused_pipe_fds(t_command *cmd_list, t_command *active_cmd);

// file_io.c
bool		validate_file_descriptors(t_io_fds *io);
bool		setup_io_redirection(t_io_fds *io);
bool		reset_io_redirection(t_io_fds *io);

// signal.c
void		handle_interrupt_prompt_reset(int signo);
void		handle_interrupt_newline(int signal);
void		disable_quit_signal(void);
void		configure_interactive_signals(void);
void		configure_noninteractive_signals(void);

#endif