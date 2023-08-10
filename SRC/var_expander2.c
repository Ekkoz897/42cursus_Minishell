/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:45:21 by miandrad          #+#    #+#             */
/*   Updated: 2023/08/10 10:17:16 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expander_helper3(char commands, int *qte, int *sqte, char *curr_qte)
{
	if (commands == '\"' && *qte == -1
		&& (*sqte == -1 || *curr_qte == '\"'))
	{
		*sqte *= -1;
		if (*sqte == 1)
			*curr_qte = '\"';
		else
			*curr_qte = '\0';
	}
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
		if (in_squotes == -1 && commands[i][j] == '$')
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
