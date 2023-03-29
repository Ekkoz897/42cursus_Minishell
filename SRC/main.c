/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/03/29 16:15:14 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// Function takes the input string and splits the commands into one array each 
// their with flags
char	**ft_split_cmds(char *input)
{
	int		i;
	int		j;
	int		k;
	char	**cmds;

	i = 0;
	cmds = ft_calloc(1, sizeof(char *));
	while (input[i])
	{
		if (input[i] == '|')
		{
			free (cmds);
			cmds = ft_calloc(3, sizeof(char *));
			j = i;
			cmds[0] = ft_calloc(j + 1, sizeof(char));
			while (j >= 0)
			{
				cmds[0][j] = input[j];
				j--;
			}
			cmds[1] = ft_calloc(2, sizeof(char));
			cmds[1][0] = '|';
			while (input[i++])
				j++;
			cmds[2] = ft_calloc(j, sizeof(char));
			while (j >= 0)
			{
				cmds[2][j] = input[i];
				j--;
				i--;
			}
		}
		i++;
	}
	
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	// char	**commands;

	(void)ac;
	(void)av;
	(void)env;
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
		commands_cpy(input);
		
		free(input);
	}
	return (0);
}
