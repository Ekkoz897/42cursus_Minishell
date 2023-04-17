/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/04/17 15:31:25 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	char	*input;
	char	**commands;
	t_vars	vars;
	int		pipe_fd[2];

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("myshell> ");
		if (!input)
		{
			ft_printf("\n");
			break ;
		}
		add_history(input);
		commands = ft_split_commands(input, "|");
		i = 0;
		while (commands[i])
		{
			ft_printf("cmd[%i] : %s\n", i, commands[i]);
			i++;
		}
		i = 0;
		vars.p0 = 0;
		while (commands[i])
		{
			first_process(&vars, env, pipe_fd, &commands[i]);
			i++;
		}
		close(pipe_fd[0]);
		waitpid(vars.pid1, NULL, 0);
		ft_free(commands);
		free(input);
	}
	return (0);
}

// To print the commands stored in the array
		// if (commands)
		// 	ft_printf("cmd[0] = %s\n", commands[0]);
		// if (commands[1])
		// 	ft_printf("cmd[1] = %s\n", commands[1]);
		// if (commands[2])
		// 	ft_printf("cmd[2] = %s\n", commands[2]);