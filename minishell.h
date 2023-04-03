/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 10:00:01 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/wait.h>
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
	int		fd2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_flags;
	char	**cmd2_flags;
}t_vars;

// Struct for commands list
typedef struct s_cmds
{
	void			**content;
	struct s_cmds	*next;
}t_cmds;

// Input Sanitize.c
size_t	commands_cpy(char *s);
void	ft_free(char **array);
char	*find_path(char **envp);
char	*check_valid_cmd(char *argv, char **envp);

// ft_split_cmds.c
t_cmds	*ft_split_commands(const char *str, const char *delimiters);
int		count_words(const char *str, const char *delimiters);

// Processes.c
void	first_process(t_vars *vars, char **envp, int *pipe_fd);
void	second_process(t_vars *vars, char **envp, int *pipe_fd);

// utils.c
t_cmds	*create_new_node(char **command);
t_cmds	*link_new_node(t_cmds *current, char **commands);

#endif