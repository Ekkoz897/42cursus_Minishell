/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 13:01:03 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

// Same struct used in Pipex
typedef struct s_vars
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		fd1;
	int		fd0;
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
size_t		commands_cpy(char *s);
void		ft_free(char **array);
char		*find_path(char **envp);
char		*check_valid_cmd(char *argv, char **envp);

// ft_split_cmds.c
int			get_token_length(const char *str, const char *delimiters);
const char	*get_next_token(const char *str, const char *delimiters);
char		**ft_split_commands(const char *str, const char *delimiters);

// Processes.c
void	first_process(t_vars *vars, char **envp, int *pipe_fd, char **commands);
void		second_process(t_vars *vars, char **envp, int *pipe_fd);

// utils.c
char	**ft_split_commands_no_redirection(const char *str, const char *delimiters);
int			count_words(const char *str, const char *delimiters);

#endif