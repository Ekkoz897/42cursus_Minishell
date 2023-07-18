/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:52:08 by apereira          #+#    #+#             */
/*   Updated: 2023/07/18 12:55:32 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Receives the signal and handles it if it is CTRL+C
// RL_on_new_line() moves the cursor to the next line
// RL_redisplays() redisplays the prompt "myshell>"
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		SIG_IGN ;
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->cmd_flags)
	{
		ft_free(vars->cmd_flags);
		vars->cmd_flags = NULL;
	}
	if (vars->here_doc_fd)
	{
		free(vars->here_doc_fd);
		vars->here_doc_fd = NULL;
	}
}

void	ft_vars_init(t_vars *vars)
{
	vars->num_env_vars = 0;
	vars->here_doc_fd = NULL;
	vars->my_environ = NULL;
	vars->cmd2_flags = NULL;
	vars->cmd2_path = NULL;
	vars->cmd_flags = NULL;
	vars->cmd1_path = NULL;
	vars->temp = NULL;
}

int	setup_pipe(int	*pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		perror("Pipe");
		return (0);
	}
	return (1);
}
