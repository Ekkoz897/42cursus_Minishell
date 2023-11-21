/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:45:21 by miandrad          #+#    #+#             */
/*   Updated: 2023/11/16 08:01:49 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_exit_status(t_vars *vars, char *commands, int j)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(commands, 0, j - 2);
	temp2 = ft_substr(commands, j, ft_strlen(commands) - j);
	free (commands);
	commands = ft_strjoin_three(temp, ft_itoa(vars->exit_stat), temp2);
	free (temp);
	return (commands);
}

int	check_if_exit_stat(char **commands, int i, t_vars *vars, int j)
{
	if (commands[i][j] == '$' && commands[i][j + 1] == '?')
	{
		commands[i] = replace_exit_status(vars, commands[i], j + 2);
		return (1);
	}
	return (0);
}

void	ft_expander_helper2(char **commands, t_vars *vars, int i)
{
	int		j;
	int		in_quotes;
	int		in_squotes;

	j = 0;
	in_quotes = -1;
	in_squotes = -1;
	while (commands[i][j])
	{
		if (in_squotes == -1 && check_if_exit_stat(commands, i, vars, j))
			continue ;
		else if (in_squotes == -1 && commands[i][j] == '$')
		{
			commands[i] = replace_var(vars, commands[i], j + 1);
			if (!commands[i])
				return ;
		}
		if (commands[i][j] == '"' && in_squotes == -1 && in_quotes == -1)
			in_quotes *= -1;
		if (commands[i][j] == 39 && in_quotes == -1 && in_squotes == -1)
			in_squotes *= -1;
		j++;
	}
}
