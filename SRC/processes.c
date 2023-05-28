/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:00:07 by apereira          #+#    #+#             */
/*   Updated: 2023/05/28 12:24:21 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_input_redirection(char **commands, t_vars *vars)
{
	char		*infile;
	char		*temp;
	int			i;

	i = 0;
	temp = ft_strrchr(commands[0], '<');
	temp++;
	while (*temp == ' ' || *temp == '	')
		temp++;
	while (temp[i] != ' ' && temp[i] != '	' && temp[i])
		i++;
	infile = ft_strndup(temp, i);
	i = 0;
	if (*(ft_strrchr(commands[0], '<') - 1) == '<')
		vars->fd0 = vars->here_doc_fd[i];
	else
		vars->fd0 = open(infile, O_RDONLY);
	if (vars->fd0 < 0)
	{
		perror(infile);
		return (0);
	}
	return (1);
}

int	setup_output_redirection(char **commands, t_vars *vars)
{
	char		*outfile;
	char		*temp;
	int			i;

	i = 0;
	temp = ft_strrchr(commands[0], '>');
	temp++;
	while (*temp == ' ' || *temp == '	')
		temp++;
	while (temp[i] != ' ' && temp[i] != '	' && temp[i])
		i++;
	outfile = ft_strndup(temp, i);
	if (*(ft_strrchr(commands[0], '>') - 1) == '>')
		vars->fd1 = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0000644);
	else
		vars->fd1 = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (vars->fd1 < 0)
	{
		perror(outfile);
		return (0);
	}
	return (1);
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

// signals para evitar o double prompt "minishell>minishell>"
void	execute_command(t_vars *vars, char **commands, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	vars->cmd1_path = check_valid_cmd(vars->cmd_flags[0], envp);
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
	execve(vars->cmd1_path, vars->cmd_flags, envp);
}

void	first_process(t_vars *vars, char **envp, char **commands)
{
	vars->fd0 = 0;
	vars->fd1 = 1;
	vars->cmd_flags = ft_split_commands_no_redirection(commands[0], " |<>");
	if (ft_strrchr(commands[0], '<'))
		setup_input_redirection(commands, vars);
	if (ft_strrchr(commands[0], '>'))
		setup_output_redirection(commands, vars);
	if (!setup_pipe(vars->pipe_fd))
		exit(1);
	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return ;
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
}
