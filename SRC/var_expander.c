/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:02:13 by apereira          #+#    #+#             */
/*   Updated: 2023/08/09 11:41:08 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_var(t_vars *vars, char *commands, int j)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		k;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	while (commands[j + i] && ((commands[j + i] >= 'a' && commands[j + i] \
		<= 'z') || (commands[j + i] >= 'A' && commands[j + i] <= 'Z')))
	{
		tmp2 = tmp;
		tmp = ft_strjoin_char(tmp, commands[j + i]);
		i++;
		free (tmp2);
	}
	k = 0;
	while (vars->my_environ[k] && !ft_strnstr(vars->my_environ[k], tmp, \
			ft_strlen(tmp)))
		k++;
	tmp2 = get_value_for_expand(vars->my_environ[k]);
	k = 0;
	free (tmp);
	tmp = NULL;
	while (k < j - 1 && commands[k])
	{
		if (tmp)
		{
			tmp3 = ft_strdup(tmp);
			free (tmp);
		}
		tmp = ft_strjoin_char(tmp3, commands[k]);
		free(tmp3);
		k++;
	}
	tmp3 = ft_strjoin_three(tmp, tmp2, &commands[i + j]);
	if (tmp)
		free(tmp);
	free(commands);
	return (tmp3);
}

void	var_expander(t_vars *vars, char **commands)
{
	int		i;
	int		j;
	int		in_quotes;
	int		in_squotes;
	char	current_quote;

	i = 0;
	in_quotes = -1;
	in_squotes = -1;
	current_quote = '\0';
	while (commands[i])
	{
		if (strchr(commands[i], '$'))
		{
			j = 0;
			while (commands[i][j])
			{
				if (in_squotes == -1 && commands[i][j] == '$')
				{
					commands[i] = replace_var(vars, commands[i], j + 1);
					j = 0;
				}
				if (commands[i][j] == '\"' && in_squotes == -1
					&& (in_quotes == -1 || current_quote == '\"'))
				{
					in_quotes *= -1;
					if (in_quotes == 1)
						current_quote = '\"';
					else
						current_quote = '\0';
				}
				if (commands[i][j] == '\'' && in_quotes == -1
					&& (in_squotes == -1 || current_quote == '\''))
				{
					in_squotes *= -1;
					if (in_squotes == 1)
						current_quote = '\'';
					else
						current_quote = '\0';
				}
				j++;
			}
		}
		i++;
	}
}
