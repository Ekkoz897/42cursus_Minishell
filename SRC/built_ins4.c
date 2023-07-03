/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:58:20 by apereira          #+#    #+#             */
/*   Updated: 2023/07/03 12:05:26 by miandrad         ###   ########.fr       */
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
	exit(0);
}
