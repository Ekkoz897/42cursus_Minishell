/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/03/31 14:44:25 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
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
		ft_printf("You entered: %s\n", input);
		commands = ft_split_cmds(input, ' ');
		if (commands)
			ft_printf("cmd[0] = %s\n", commands[0]);
		vars.cmd1_flags = ft_split(commands[0], ' ');
		if (commands[1])
			ft_printf("cmd[1] = %s\n", commands[1]);
		if (commands[2])
			ft_printf("cmd[2] = %s\n", commands[2]);
		first_process(&vars, env, pipe_fd);
		ft_free(commands);
		ft_free(vars.cmd1_flags);
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