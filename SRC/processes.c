/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:00:07 by apereira          #+#    #+#             */
/*   Updated: 2023/04/17 15:31:56 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_process(t_vars *vars, char **envp, int *pipe_fd, char **commands)
{
	char		*infile;
	char		*temp;
	int			i;
	// char	*outfile;

	vars->fd0 = 0;
	i = 0;
	vars->cmd_flags = ft_split_commands_no_redirection(commands[0], " ");
	ft_printf("vars->cmd_falgs : %s\n", vars->cmd_flags[0]);
	if (ft_strrchr(commands[0], '<'))
	{
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
			return ;
		}
	}
	if (pipe(pipe_fd) < 0)
	{
		perror("Pipe");
		exit(1);
	}
	ft_printf("%i, %i\n", pipe_fd[0], pipe_fd[1]);
	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return ;
	if (vars->pid1 == 0)
	{
		vars->cmd1_path = check_valid_cmd(vars->cmd_flags[0], envp);
		if (vars->cmd1_path == NULL)
			exit(1);
		if (commands[1])
			dup2(pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		if (vars->fd0 != 0)
			dup2(vars->fd0, STDIN_FILENO);
		else if (vars->p0 != 0)
			dup2(vars->p0, STDIN_FILENO);
		execve(vars->cmd1_path, vars->cmd_flags, envp);
	}
	close(pipe_fd[1]);
	if (vars->p0 != 0)
		close(vars->p0);
	vars->p0 = pipe_fd[0];
}

void	second_process(t_vars *vars, char **envp, int *pipe_fd)
{
	(void)pipe_fd;
	vars->pid2 = fork();
	if (vars->pid2 < 0)
		return ;
	if (vars->pid2 == 0)
	{
		vars->cmd2_path = check_valid_cmd(vars->cmd2_flags[0], envp);
		if (!vars->cmd2_path)
			exit(1);
		execve(vars->cmd2_path, vars->cmd2_flags, envp);
	}
}
