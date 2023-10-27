/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:45:21 by miandrad          #+#    #+#             */
/*   Updated: 2023/10/27 14:20:19 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expander_helper3(char commands, int *in_quotes, int *in_squotes,
	char *current_quote)
{
	if (commands == 39 && *in_quotes == -1
		&& (*in_squotes == -1 || *current_quote == '"'))
	{
		*in_squotes *= -1;
		if (*in_squotes == 1)
			*current_quote = '"';
		else
			*current_quote = '\0';
	}
}

char	*replace_exit_status(t_vars *vars, char *commands, int j)
{
	char	*temp;

	temp = ft_substr(commands, j, ft_strlen(commands) - j);
	free (commands);
	commands = ft_strjoin_three("echo ", ft_itoa(vars->exit_stat), temp);
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
	char	current_quote;

	j = 0;
	in_quotes = -1;
	in_squotes = -1;
	current_quote = '\0';
	while (commands[i][j])
	{
		if (in_squotes == -1 && check_if_exit_stat(commands, i, vars, j))
			return ;
		else if (in_squotes == -1 && commands[i][j] == '$')
		{
			commands[i] = replace_var(vars, commands[i], j + 1);
			j = 0;
		}
		ft_expander_helper(commands[i][j], &in_quotes,
			&in_squotes, &current_quote);
		ft_expander_helper3(commands[i][j], &in_quotes,
			&in_squotes, &current_quote);
		j++;
	}
}
