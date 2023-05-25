/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:58:20 by apereira          #+#    #+#             */
/*   Updated: 2023/05/25 14:06:41 by apereira         ###   ########.fr       */
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
