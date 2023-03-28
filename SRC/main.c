/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/03/28 15:13:24 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**commands;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("myshell> ");
		if (!input)
		{
			ft_printf("\n");
			break ;
		}
		add_history(input);
		ft_printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}
