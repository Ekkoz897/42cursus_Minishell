/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:27:54 by apereira          #+#    #+#             */
/*   Updated: 2023/05/13 11:34:56 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtin(char **commands)
{
	if (ft_strcmp(commands[0], "echo") == 0)
		ft_echo(commands);
	// else if (ft_strcmp(commands[0], "cd") == 0)
	// 	ft_cd(commands);
	// else if (ft_strcmp(commands[0], "pwd") == 0)
	// 	ft_pwd();
	// else if (ft_strcmp(commands[0], "export") == 0)
	// 	ft_export(commands);
	// else if (ft_strcmp(commands[0], "unset") == 0)
	// 	ft_unset(commands);
	// else if (ft_strcmp(commands[0], "env") == 0)
	// 	ft_env(commands);
	// else if (ft_strcmp(commands[0], "exit") == 0)
	// 	ft_exit(commands);
	else
		return (0);
	return (1);
}

void	ft_echo(char **commands)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (commands[1] && ft_strcmp(commands[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (commands[i])
	{
		ft_printf("%s", commands[i]);
		if (commands[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n_flag)
		ft_printf("\n");
}
