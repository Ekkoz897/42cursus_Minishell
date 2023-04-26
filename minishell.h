/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
/*   Updated: 2023/04/26 11:27:34 by apereira         ###   ########.fr       */
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
# include "ft_printf/ft_printf.h"

// Same struct used in Pipex
typedef struct s_vars
{
	int		fd[2];
	int		pid1;
	int		fd1;
	int		fd0;
	int		p0;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd_flags;
	char	**cmd2_flags;
}t_vars;

// Struct for commands list
typedef struct s_cmds
{
	void			**content;
	struct s_cmds	*next;
}t_cmds;

// Input Sanitize.c
char		*check_valid_cmd(char *argv, char **envp);

// ft_split_cmds.c
int			get_token_length(const char *str, const char *delimiters);
const char	*get_next_token(const char *str, const char *delimiters);
char		**ft_split_commands(const char *str, const char *delimiters);

// Processes.c
int			setup_input_redirection(char **commands, t_vars *vars);
int			setup_output_redirection(char **commands, t_vars *vars);
int			setup_pipe(int	*pipe_fd);
void		execute_command(t_vars *vars, char **commands, char **envp,
				int *pipe_fd);
void		first_process(t_vars *vars, char **envp, int *pipe_fd,
				char **commands);
// void		second_process(t_vars *vars, char **envp, int *pipe_fd);

// utils.c
char		*find_path(char **envp);
void		ft_free(char **array);
int			count_words(const char *str, const char *delimiters);

// util2.c
char		**ft_split_commands_no_redirection(char *str,
				char *delimiters);
int			is_delimiter(char c, char *delimiters);
int			count_words_no_redirection(char *str, char *delimiters);
char		*get_next_token_no_redirection(char *str,
				char *delimiters);
int			get_token_length_no_redirection(char *str,
				char *delimiters);

// signal_handler.c
void		signal_handler(int signal);
#endif
