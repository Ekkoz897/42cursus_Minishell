/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/03/29 11:47:51 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_cmds2(char **cmds, char *input, int i)
{
	int	j;

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
			j = 0;
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
	return (cmds);
}

// Function takes the input string and splits the commands into one array each 
// with their with flags
char	**ft_split_cmds(char *input)
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = ft_calloc(2, sizeof(char *));
	if (ft_strchr(input, '|') != NULL)
		ft_split_cmds2(cmds, input, i);
	else
	{
		i = 0;
		while (input[i])
		{
			cmds[0] = ft_calloc(ft_strlen(input), sizeof(char));
			cmds[0][i] = input[i];
			ft_printf("%s\n", cmds[0]);
			i++;
		}
	}
	return (cmds);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**commands;

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
		commands = ft_split_cmds(input);
		if (commands)
			ft_printf("%s\n", *commands[0]);
		ft_printf("You entered: %s\n", input);
		commands_cpy(input);
		free(input);
	}
	return (0);
}
