/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:27:54 by apereira          #+#    #+#             */
/*   Updated: 2023/05/13 12:53:02 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtin(char **commands)
{
	char	**split_cmds;

	split_cmds = ft_split(commands[0], ' ');
	if (ft_strcmp(split_cmds[0], "echo") == 0)
		ft_echo(split_cmds);
	else if (ft_strcmp(split_cmds[0], "cd") == 0)
		ft_cd(split_cmds);
	else if (ft_strcmp(split_cmds[0], "pwd") == 0)
		ft_pwd();
	// else if (ft_strcmp(split_cmds[0], "export") == 0)
	// 	ft_export(split_cmds);
	// else if (ft_strcmp(split_cmds[0], "unset") == 0)
	// 	ft_unset(split_cmds);
	// else if (ft_strcmp(split_cmds[0], "env") == 0)
	// 	ft_env(split_cmds);
	// else if (ft_strcmp(split_cmds[0], "exit") == 0)
	// 	ft_exit(split_cmds);
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

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	else
		perror("pwd");
}

void	ft_cd(char **commands)
{
	char	*home;
	char	*pwd;
	char	*old_pwd;

	home = getenv("HOME");
	old_pwd = getenv("OLDPWD");
	pwd = getenv("PWD");
	if (!commands[1])
	{
		if (home)
			chdir(home);
		else
			ft_printf("cd: HOME not set\n");
	}
	else if (ft_strcmp(commands[1], "-") == 0)
	{
		if (old_pwd && chdir(old_pwd) == 0)
		{
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", old_pwd, 1);
		}
		if (pwd)
			chdir(pwd);
		else
			ft_printf("cd: OLDPWD not set\n");
	}
	else if (chdir(commands[1]) == -1)
		perror(commands[1]);
}
