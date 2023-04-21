/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:00:07 by apereira          #+#    #+#             */
/*   Updated: 2023/04/21 11:55:52 by apereira         ###   ########.fr       */
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
	int			flag;

	i = 0;
	flag = 0;
	temp = ft_strrchr(commands[0], '>');
	if (commands[0][ft_strlen(commands[0]) - ft_strlen(temp) - 1] == '>')
		flag = 1;
	temp++;
	while (*temp == ' ' || *temp == '	')
		temp++;
	while (temp[i] != ' ' && temp[i] != '	' && temp[i])
		i++;
	outfile = ft_strndup(temp, i);
	if (flag == 1)
		vars->fd1 = open(outfile, O_CREAT | O_RDWR, 0000644);
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

void	execute_command(t_vars *vars, char **commands, char **envp,
		int *pipe_fd)
{
	vars->cmd1_path = check_valid_cmd(vars->cmd_flags[0], envp);
	if (vars->cmd1_path == NULL)
		exit(1);
	ft_printf("vars->fd1 %i\n", vars->fd1);
	if (vars->fd1 != 1)
	{
		dup2(vars->fd1, STDOUT_FILENO);
		close(vars->fd1);
	}
	else if (commands[1])
		dup2(pipe_fd[1], STDOUT_FILENO);
	close (pipe_fd[0]);
	if (vars->fd0 != 0)
	{
		dup2(vars->fd0, STDIN_FILENO);
		close(vars->fd0);
	}
	else if (vars->p0 != 0)
		dup2(vars->p0, STDIN_FILENO);
	execve(vars->cmd1_path, vars->cmd_flags, envp);
}

void	first_process(t_vars *vars, char **envp, int *pipe_fd, char **commands)
{
	vars->fd0 = 0;
	vars->fd1 = 1;
	vars->cmd_flags = ft_split_commands_no_redirection(commands[0], " |<>");
	ft_printf("vars->cmd_flags : %s\n", vars->cmd_flags[1]);
	if (ft_strrchr(commands[0], '<'))
		setup_input_redirection(commands, vars);
	if (ft_strrchr(commands[0], '>'))
		setup_output_redirection(commands, vars);
	if (!setup_pipe(pipe_fd))
		exit(1);
	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return ;
	if (vars->pid1 == 0)
		execute_command(vars, commands, envp, pipe_fd);
	if (vars->fd1 != 1)
		close(vars->fd1);
	if (vars->fd0 != 0)
		close(vars->fd0);
	close(pipe_fd[1]);
	if (vars->p0 != 0)
		close(vars->p0);
	vars->p0 = pipe_fd[0];
}
