/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:58:20 by apereira          #+#    #+#             */
/*   Updated: 2023/07/13 12:55:19 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	env_num(t_vars *vars, char **commands)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	while (vars->my_environ[i] != NULL)
	{
		x = 1;
		while (commands[x])
		{
			if (ft_strncmp(commands[x], vars->my_environ[i], ft_strlen(commands[x])) == 0)
				j++;
			x++;
		}
		i++;
	}
	return (j);
}

// Clears value form env variables, otherwise does nothing
void	ft_unset(t_vars *vars, char **commands)
{
	int		i;
	int		j;
	int		x;
	int		flag;
	char	**new_environ;

	i = 0;
	j = 0;
	flag = 1;
	vars->num_env_vars = vars->num_env_vars - env_num(vars, commands);
	new_environ = malloc(sizeof(char *) * (vars->num_env_vars + 1));
	while (vars->my_environ[i] != NULL)
	{
		x = 1;
		while (commands[x])
		{
			if (ft_strncmp(commands[x], vars->my_environ[i], ft_strlen(commands[x])) == 0)
				flag = 0;
			x++;
		}
		if (flag == 1)
		{
			new_environ[j] = ft_strdup(vars->my_environ[i]);
			j++;
		}
		flag = 1;
		i++;
	}
	new_environ[j] = NULL;
	ft_free(vars->my_environ);
	vars->my_environ = new_environ;
}

int	check_cd_ex_uns(char **commands, t_vars *vars)
{
	char	**split_cmds;

	split_cmds = ft_split(commands[0], ' ');
	if (ft_strcmp(split_cmds[0], "cd") == 0)
		ft_cd(split_cmds, vars);
	else if (ft_strcmp(split_cmds[0], "exit") == 0)
		ft_exit(split_cmds);
	else if (ft_strcmp(split_cmds[0], "unset") == 0)
		ft_unset(vars, split_cmds);
	else if (ft_strcmp(split_cmds[0], "export") == 0 && split_cmds[1])
		ft_export(vars, split_cmds);
	else
	{
		ft_free(split_cmds);
		return (0);
	}
	ft_free(split_cmds);
	return (1);
}
