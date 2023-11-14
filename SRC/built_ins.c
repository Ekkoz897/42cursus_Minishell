/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:27:54 by apereira          #+#    #+#             */
/*   Updated: 2023/11/14 18:38:03 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtin(char **commands, t_vars *vars)
{
	char	**split_cmds;
	
	split_cmds = ft_split(commands[0], ' ');
	if (ft_strcmp(vars->cmd_flags[0], "echo") == 0)
		ft_echo(vars->cmd_flags);
	else if (ft_strcmp(vars->cmd_flags[0], "cd") == 0)
		ft_cd(vars->cmd_flags, vars);
	else if (ft_strcmp(split_cmds[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(split_cmds[0], "export") == 0 && !split_cmds[1])
		ft_export(vars, split_cmds);
	else if (ft_strcmp(split_cmds[0], "env") == 0)
		ft_env(vars);
	else if (ft_strcmp(split_cmds[0], "exit") == 0)
		ft_exit(split_cmds);
	else
		return (0);
	return (1);
}

void	ft_echo2(char **commands, int i)
{
	while (commands[i])
	{
		ft_printf("%s", commands[i]);
		if (commands[i + 1])
			ft_printf(" ");
		i++;
	}
}

void	ft_echo(char **commands)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (commands[1] && check_flag_n(commands[1]) == 1)
	{
		n_flag = 1;
		i++;
	}
	ft_echo2(commands, i);
	if (!n_flag)
		ft_printf("\n");
	exit (0);
}

void	change_directory(char *path, t_vars *vars)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*temp;

	old_pwd = get_env_var(vars, "PWD");
	temp = old_pwd;
	if (chdir(path) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		modify_env_var(vars, "OLDPWD", temp);
		modify_env_var(vars, "PWD", new_pwd);
		free(new_pwd);
	}
	else
		perror(path);
}

void	ft_cd(char **commands, t_vars *vars)
{
	char	*home;
	char	*old_pwd;

	home = get_env_var(vars, "HOME");
	old_pwd = get_env_var(vars, "OLDPWD");
	if (!commands[1])
	{
		if (home)
			change_directory(home, vars);
		else
			ft_printf("cd: HOME not set\n");
	}
	else if (ft_strcmp(commands[1], "-") == 0)
	{
		old_pwd = get_env_var(vars, "OLDPWD");
		if (old_pwd)
			change_directory(old_pwd, vars);
		else
			ft_printf("cd: OLDPWD not set\n");
	}
	else
		change_directory(commands[1], vars);
}
