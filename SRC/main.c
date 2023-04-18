/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/04/18 10:34:52 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// To print the commands stored in the array
		// if (commands)
		// 	ft_printf("cmd[0] = %s\n", commands[0]);
		// if (commands[1])
		// 	ft_printf("cmd[1] = %s\n", commands[1]);
		// if (commands[2])
		// 	ft_printf("cmd[2] = %s\n", commands[2]);

void	minishell(char *input, char **env)
{
	char	**commands;
	int		i;
	t_vars	vars;
	int		pipe_fd[2];

	commands = ft_split_commands(input, "|");
	i = 0;
	vars.p0 = 0;
	while (commands[i])
	{
		first_process(&vars, env, pipe_fd, &commands[i]);
		i++;
	}
	close(pipe_fd[0]);
	while (i-- > 0)
		wait(NULL);
	if (commands)
		ft_free(commands);
	if (input)
		free(input);
	input = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("myshell> ");
		add_history(input);
		if (ft_strlen(input) != 0)
			minishell(input, env);
	}
	return (0);
}
