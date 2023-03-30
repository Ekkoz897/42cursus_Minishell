/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:00:07 by apereira          #+#    #+#             */
/*   Updated: 2023/03/30 09:37:08 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_process(t_vars *vars, char **envp, int *pipe_fd)
{
	(void)pipe_fd;

	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return ;
	if (vars->pid1 == 0)
	{
		vars->cmd1_path = check_valid_cmd(vars->cmd1_flags[0], envp);
		if (vars->cmd1_path == NULL)
			exit(1);
		execve(vars->cmd1_path, vars->cmd1_flags, envp);
	}
	waitpid(vars->pid1, NULL, 0);
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
