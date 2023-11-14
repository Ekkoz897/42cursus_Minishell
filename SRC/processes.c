/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:00:07 by apereira          #+#    #+#             */
/*   Updated: 2023/11/14 01:14:09 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_file_opening(char *str, t_vars *vars, char *infile, int *j)
{
	if (*(ft_strrchr(str, '<') - 1) == '<')
	{
		vars->fd0 = vars->here_doc_fd[*j];
		(*j)++;
	}
	else
		vars->fd0 = open(infile, O_RDONLY);
	// if (vars->fd0 < 0)
	// {
	// 	perror(infile);
	// 	free(infile);
	// 	exit(0);
	// }
	free(infile);
}

int	setup_input_redirection(char **commands, t_vars *vars, int *j)
{
	char	*infile;
	char	*temp;
	int		i;
	int		in_quotes;

	temp = commands[0];
	in_quotes = -1;
	while (temp && *temp && *temp != '>')
	{
		if (*temp == '"' || *temp == 39)
			in_quotes *= -1;
		temp++;
	}
	if (in_quotes == 1)
		return (0);
	temp = ft_strrchr(commands[0], '<');
	temp++;
	while (*temp == ' ' || *temp == '	')
		temp++;
	i = 0;
	while (temp[i] != ' ' && temp[i] != '	' && temp[i])
		i++;
	infile = ft_strndup(temp, i);
	handle_file_opening(commands[0], vars, infile, j);
	return (1);
}

int	setup_output_redirection(char **commands, t_vars *vars)
{
	char		*outfile;
	char		*temp;
	int			in_quotes;

	outfile = NULL;
	temp = (commands[0]);
	in_quotes = -1;
	while (temp && *temp != '>')
	{
		if (*temp == '"' || *temp == 39)
			in_quotes *= -1;
		temp++;
	}
	if (in_quotes == 1)
		return (0);
	outfile = setup_output_redirection_help(commands, vars, temp, outfile);
	if (vars->fd1 < 0)
	{
		perror(outfile);
		return (0);
	}
	return (1);
}

// signals para evitar o double prompt "minishell>minishell>"
void	execute_command(t_vars *vars, char **commands, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	remove_quotes_from_array(vars->cmd_flags);
	vars->cmd1_path = check_valid_cmd(vars->cmd_flags[0], vars->my_environ);
	if (vars->cmd1_path == NULL)
		exit(1);
	if (vars->fd1 != 1)
	{
		dup2(vars->fd1, STDOUT_FILENO);
		close(vars->fd1);
	}
	else if (commands[1])
		dup2(vars->pipe_fd[1], STDOUT_FILENO);
	close (vars->pipe_fd[0]);
	if (vars->fd0 != 0)
	{
		dup2(vars->fd0, STDIN_FILENO);
		close(vars->fd0);
	}
	else if (vars->p0 != 0)
		dup2(vars->p0, STDIN_FILENO);
	if (!check_if_builtin(commands, vars))
		execve(vars->cmd1_path, vars->cmd_flags, envp);
}

void	first_process(t_vars *vars, char **envp, char **commands, int *j)
{
	vars->fd0 = 0;
	vars->fd1 = 1;
	vars->cmd_flags = ft_split_commands_no_redirection(commands[0], " |<>");
	if (ft_strrchr(commands[0], '<'))
		setup_input_redirection(commands, vars, j);
	if (ft_strrchr(commands[0], '>'))
		setup_output_redirection(commands, vars);
	if (!setup_pipe(vars->pipe_fd))
		exit(1);
	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return ;
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_quit_ctrlc);
	if (vars->pid1 == 0)
		execute_command(vars, commands, envp);
	if (vars->fd1 != 1)
		close(vars->fd1);
	if (vars->fd0 != 0)
		close(vars->fd0);
	close(vars->pipe_fd[1]);
	if (vars->p0 != 0)
		close(vars->p0);
	vars->p0 = vars->pipe_fd[0];
	wait(&vars->pid1);
	if (vars->temp != NULL)
	{
		unlink(vars->temp);
		free(vars->temp);	
		vars->temp = NULL;
	}
}
