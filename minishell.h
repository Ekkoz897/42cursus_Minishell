/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
/*   Updated: 2023/03/30 09:36:33 by miandrad         ###   ########.fr       */
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

// Input Sanitize.c
size_t			commands_cpy(char *s);
void			ft_free(char **array);
char			*ft_commands(char *s);
char			*find_path(char **envp);
char			*check_valid_cmd(char *argv, char **envp);

// Processes.c
void			first_process(t_vars *vars, char **envp, int *pipe_fd);
void			second_process(t_vars *vars, char **envp, int *pipe_fd);

#endif