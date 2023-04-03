/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:00:07 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 13:15:27 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_process(t_vars *vars, char **envp, int *pipe_fd, char **commands)
{
	char	*infile;
	// char	*outfile;
	char	*temp;
	int		i;

	vars->fd0 = 0;
	i = 0;
	vars->cmd_flags = ft_split_commands_no_redirection(commands[0], " ");
	if (ft_strrchr(commands[0], '<'))
	{
		ft_printf("aqun\n");
		temp = ft_strrchr(commands[0], '<');
		temp++;
		while (*temp == ' ' || *temp == '	')
			temp++;
		while (temp[i] != ' ' && temp[i] != '	' && temp[i])
			i++;
		infile = ft_strndup(temp, i);
		ft_printf("%s; infile :\n", infile);
		vars->fd0 = open(infile, O_RDONLY);
		if (vars->fd0 < 0)
		{
			perror("Infile");
			return ;
		}
	}
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
		//  close (pipe_fd[0]);
		if (vars->fd0 == 0)
			dup2(vars->fd0, STDIN_FILENO);
		execve(vars->cmd1_path, vars->cmd_flags, envp);
	}
}

// Opens the second file FD, parses the second command by duplicating it
// and executes it. Passes the output onto the second file instead of
// to the standard output.
// O_TRUNC deletes file contents so we can write to the file, O_CREAT creates 
// a file if there isn't one available, O_RDWR opens a FD to read and write.
// The number sets the perms of the file so it can be read from and wrote on.
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
