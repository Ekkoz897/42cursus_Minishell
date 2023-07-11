/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:58:20 by apereira          #+#    #+#             */
/*   Updated: 2023/07/11 13:26:14 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// Clears value form env variables, otherwise does nothing
void	ft_unset(t_vars *vars, char **commands)
{
	int	i;
	int	j;

	i = 1;
	while (commands[i])
	{
		j = 0;
		while (vars->my_environ[j])
		{
			if (ft_strncmp(commands[i], vars->my_environ[j],
					ft_strlen(commands[i])) == 0)
			{
				free(vars->my_environ[j]);
				vars->my_environ[j] = NULL;
			}
			j++;
		}
		i++;
	}
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
