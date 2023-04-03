/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 10:04:09 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_vars	vars;
	t_cmds	*cmds;
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
		cmds = ft_split_commands(input, "|");
		ft_printf("cmd0 = %s\n", cmds->content);
		if (cmds->next->content)
			ft_printf("cmd1 = %s\n", *cmds->next->content);
		if (cmds->next->next->content)
			ft_printf("cmd2 = %s\n", *cmds->next->next->content);
		first_process(&vars, env, pipe_fd);
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