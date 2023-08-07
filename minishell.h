/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
/*   Updated: 2023/08/07 13:14:39 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include "GNL/get_next_line.h"
# include "ft_printf/ft_printf.h"

typedef struct s_vars
{
	int		fd[2];
	int		pipe_fd[2];
	int		pid1;
	int		fd1;
	int		fd0;
	int		p0;
	char	*temp;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd_flags;
	char	**cmd2_flags;
	char	*here_doc_fd;
	char	**my_environ;
	int		num_env_vars;
}t_vars;

// Input Sanitize.c
char		*check_executable(char *command, char **split_paths);
char		*check_command(char *command, char **split_paths);
char		*check_valid_cmd_builtin(char *command, char **split_paths);
char		*check_valid_cmd(char *argv, char **envp);

// split_cmds.c
char		*get_next_token(char *str, char *delimiters);
int			get_token_length(char *str, char *delimiters);
char		**ft_split_commands(char *str, char *delimiters);

// Processes.c
void		handle_file_opening(char *str, t_vars *vars, char *infile, int *j);
int			setup_input_redirection(char **commands, t_vars *vars, int *j);
int			setup_output_redirection(char **commands, t_vars *vars);
void		execute_command(t_vars *vars, char **commands, char **envp);
void		first_process(t_vars *vars, char **envp, char **commands, int *j);

// utils.c
char		*find_path(char **envp);
int			count_words(char *str, char *delimiters);
void		custom_handle_signal(int sign);
int			ft_strcmp(char *s1, char *s2);
int			ft_exit_ctrl_d(char *input);

// util2.c
int			get_token_length_no_redirection(char *str,
				char *delimiters);
char		*get_next_token_no_redirection(char *str,
				char *delimiters);
int			count_words_no_redirection(char *str, char *delimiters);
void		process_token(char **tokens, char **token_start,
				char *delimiters, int *i);
char		**ft_split_commands_no_redirection(char *str,
				char *delimiters);

// utils3.c
void		ft_free(char **matrix);
void		signal_handler(int sig);
void		ft_free_vars(t_vars *vars);
void		ft_vars_init(t_vars *vars);
int			setup_pipe(int	*pipe_fd);

// utils4.c
int			is_delimiter(char c, char *delimiters);
char		*remove_quotes_from_string(char *str);
void		remove_quotes_from_array(char **arr);
char		*ft_strjoin_char(char *str1, char c);
char		*get_value_for_expand(char *str);

// Built_ins.c
int			check_if_builtin(char **commands, t_vars *vars);
void		ft_echo2(char **commands, int i);
void		ft_echo(char **commands);
void		change_directory(char *path, t_vars *vars);
void		ft_cd(char **commands, t_vars *vars);

// Built_ins2.c
char		*ft_strjoin_three(char *s1, char *s2, char *s3);
void		add_env_var(t_vars *vars, char *name, char *value);
void		modify_env_var(t_vars *vars, char *name,
				char *new_value);
char		*get_env_var(t_vars *vars, char *name);
void		copy_environ(char **environ, t_vars *vars);

// Built_ins3.c
void		ft_exit(char **split_cmds);
void		ft_env(t_vars *vars);
char		*get_var_name(char *str);
char		*get_value(char *str);
void		ft_export(t_vars *vars, char **split_cmds);

// Built_ins4.c
void		ft_pwd(void);
int			env_num(t_vars *vars, char **commands);
int			is_command_in_env(char *env_var, char **commands);
void		ft_unset(t_vars *vars, char **commands);
int			check_cd_ex_uns(char **commands, t_vars *vars);

// here_doc.c
void		open_doc(t_vars *vars, char *commands, int *j);
void		open_doc_file(t_vars *vars, char *doc_file, int *j);
void		process_heredoc(t_vars *vars, char *doc_file, int fd);
void		here_doc(t_vars *vars, char **commands);
void		handle_heredoc(t_vars *vars, char *tmp, int *j);

// var_expander.c
char		*replace_var(t_vars *vars, char *commands, int j);
void		var_expander(t_vars *vars, char **commands);
#endif
