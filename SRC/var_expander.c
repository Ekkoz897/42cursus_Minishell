/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:02:13 by apereira          #+#    #+#             */
/*   Updated: 2023/08/07 13:07:13 by apereira         ###   ########.fr       */
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
	}
	ft_printf("tmp = %s\n", tmp);
	k = 0;
	while (vars->my_environ[k] && !ft_strnstr(vars->my_environ[k], tmp, \
			ft_strlen(tmp)))
		k++;
	tmp2 = get_value_for_expand(vars->my_environ[k]);
	k = 0;
	free (tmp);
	tmp = NULL;
	while (commands[k] != '$' && commands[k])
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
	ft_printf("tmp3 = %s\n", tmp3);
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
	free(commands);
	return (tmp3);
}

void	var_expander(t_vars *vars, char **commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		if (strchr(commands[i], '$'))
		{
			j = 0;
			while (commands[i][j])
			{
				if (commands[i][j] == '$')
				{
					commands[i] = replace_var(vars, commands[i], j + 1);
					ft_printf("ok\n");
					j = 0;
				}
				j++;
			}
		}
		i++;
	}
}
