/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:27:54 by apereira          #+#    #+#             */
/*   Updated: 2023/05/22 17:01:42 by apereira         ###   ########.fr       */
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
}
