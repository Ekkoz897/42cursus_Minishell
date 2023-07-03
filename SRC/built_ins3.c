/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:27:54 by apereira          #+#    #+#             */
/*   Updated: 2023/07/03 12:05:53 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// default exit success is 0, failure is 1
void	ft_exit(char **split_cmds)
{
	int	i;

	i = 0;
	while (split_cmds[i])
		i++;
	if (i == 1)
		exit(EXIT_SUCCESS);
	else if (i == 2)
	{
		if (ft_isdigit(split_cmds[1][0]))
			exit(ft_atoi(split_cmds[1]));
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				split_cmds[1]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("minishell: exit: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	ft_env(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->my_environ[i])
	{
		ft_printf("%s\n", vars->my_environ[i]);
		i++;
	}
	exit(0);
}


char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		exit(EXIT_FAILURE);
	ft_strlcpy(name, str, i + 1);
	return (name);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	j = i;
	while (str[j])
		j++;
	value = malloc(sizeof(char) * (j - i + 1));
	if (!value)
		exit(EXIT_FAILURE);
	ft_strlcpy(value, str + i, j - i + 1);
	return (value);
}


void	ft_export(t_vars *vars, char **split_cmds)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (split_cmds[i])
	{
		while (split_cmds[i])
		{
			name = get_var_name(split_cmds[i]);
			value = get_value(split_cmds[i]);
			if (name && value)
				modify_env_var(vars, name, value);
			else if (name)
				add_env_var(vars, name, "");
			free(name);
			free(value);
			i++;
		}
	}
	else
		ft_env(vars);
	exit(0);
}
