/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
/*   Updated: 2023/05/29 10:10:55 by miandrad         ###   ########.fr       */
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

// Same struct used in Pipex
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
	char		*here_doc_fd;
	char	**my_environ;
	int		num_env_vars;
}t_vars;

// Input Sanitize.c
char		*check_executable(char *command, char **split_paths);
char		*check_command(char *command, char **split_paths);
char		*check_valid_cmd(char *argv, char **envp);

// split_cmds.c
int			get_token_length(const char *str, const char *delimiters);
const char	*get_next_token(const char *str, const char *delimiters);
char		**ft_split_commands(const char *str, const char *delimiters);

// Processes.c
int			setup_input_redirection(char **commands, t_vars *vars, int *j);
int			setup_output_redirection(char **commands, t_vars *vars);
int			setup_pipe(int	*pipe_fd);
void		execute_command(t_vars *vars, char **commands, char **envp);
void		first_process(t_vars *vars, char **envp, char **commands, int *j);
// void		second_process(t_vars *vars, char **envp, int *pipe_fd);

// utils.c
char		*find_path(char **envp);
int			count_words(const char *str, const char *delimiters);
void		custom_handle_signal(int sign);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_exit_ctrl_d(char *input);

// util2.c
int			get_token_length_no_redirection(char *str,
				char *delimiters);
char		*get_next_token_no_redirection(char *str,
				char *delimiters);
int			count_words_no_redirection(char *str, char *delimiters);
int			is_delimiter(char c, char *delimiters);
char		**ft_split_commands_no_redirection(char *str,
				char *delimiters);

// utils3.c
void		ft_free(char **matrix);
void		signal_handler(int sig);

// Built_ins.c
int			check_if_builtin(char **commands, t_vars *vars);
void		ft_echo(char **commands);
void		ft_pwd(void);
void		ft_cd(char **commands, t_vars *vars);

// Built_ins2.c
char		*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
void		add_env_var(t_vars *vars, const char *name, const char *value);
void		modify_env_var(t_vars *vars, const char *name,
				const char *new_value);
char		*get_env_var(t_vars *vars, const char *name);
char		**copy_environ(char **environ);

// Built_ins3.c
void		ft_exit(char **split_cmds);
void		ft_env(t_vars *vars);
char		*get_var_name(char *str);
char		*get_value(char *str);
void		ft_export(t_vars *vars, char **split_cmds);

// Built_ins4.c
void		ft_unset(t_vars *vars, char **commands);
#endif
