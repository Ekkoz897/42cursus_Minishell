/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:02:13 by apereira          #+#    #+#             */
/*   Updated: 2023/10/27 15:06:32 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_replace_helper2(char *commands, int j, char *tmp, char **freee)
{
	int	k;

	k = 0;
	while (k < j - 1 && commands[k])
	{
		if (*freee)
		{
			tmp = ft_strdup(*freee);
			free (*freee);
		}
		*freee = ft_strjoin_char(tmp, commands[k]);
		free(tmp);
		k++;
	}
}

int	ft_replace_helper(char *commands, int j, char **tmp)
{
	int		i;
	char	*fre;

	fre = NULL;
	i = 0;
	while (commands[j + i] && ((commands[j + i] >= 'a' && commands[j + i] \
		<= 'z') || (commands[j + i] >= 'A' && commands[j + i] <= 'Z')))
	{
		fre = *tmp;
		*tmp = ft_strjoin_char(*tmp, commands[j + i]);
		i++;
		free(fre);
	}
	return (i);
}

char	*replace_var(t_vars *vars, char *commands, int j)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		k;

	tmp = NULL;
	tmp3 = NULL;
	i = ft_replace_helper(commands, j, &tmp);
	k = 0;
	if (!tmp)
		return (commands);
	while (vars->my_environ[k] && !ft_strnstr(vars->my_environ[k], tmp, \
			ft_strlen(tmp)))
		k++;
	tmp2 = get_value_for_expand(vars->my_environ[k]);
	k = 0;
	free (tmp);
	tmp = NULL;
	ft_replace_helper2(commands, j, tmp3, &tmp);
	tmp3 = ft_strjoin_three(tmp, tmp2, &commands[i + j]);
	if (tmp)
		free(tmp);
	free(commands);
	return (tmp3);
}

void	var_expander(t_vars *vars, char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (strchr(commands[i], '$'))
		{
			ft_expander_helper2(commands, vars, i);
		}
		i++;
	}
}
