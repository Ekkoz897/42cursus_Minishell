/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/05/02 15:43:50 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_doc(t_vars *vars, char *commands, int *j)
{
	char	*str;
	int		i;

	i = 0;
	commands = ft_strrchr(commands, '<');
	commands++;
	while (*commands == ' ' || *commands == '	')
		commands++;
	while (commands[i] != ' ' && commands[i] != '	' && commands[i])
		i++;
	vars->here_doc_fd[*j] = open("./TMP", __O_TMPFILE | O_RDWR, 0000644);
	str = get_next_line(0);
	while (ft_strncmp(str, commands, ft_strlen(str)) != 0)
	{
		free(str);
		str = get_next_line(0);
	}
	free(str);
	(*j)++;
}

void	here_doc(t_vars *vars, char **commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		if (ft_strrchr(commands[i], '<') && *(ft_strrchr(commands[i], \
			'<') - 1) == '<')
			j++;
		i++;
	}
	vars->here_doc_fd = malloc(sizeof(int) * j + 1);
	vars->here_doc_fd[j] = '\0';
	i = 0;
	j = 0;
	while (commands[i])
	{
		if (ft_strrchr(commands[i], '<') && *(ft_strrchr(commands[i], \
			'<') - 1) == '<')
			open_doc(vars, commands[i], &j);
		i++;
	}
}

// To print the commands stored in the array
	// if (commands)
	// 	ft_printf("cmd[0] = %s\n", commands[0]);
	// if (commands[1])
	// 	ft_printf("cmd[1] = %s\n", commands[1]);
	// if (commands[2])
	// 	ft_printf("cmd[2] = %s\n", commands[2]);

void	minishell(char *input, char **env)
{
	char	**commands;
	int		i;
	t_vars	vars;
	int		pipe_fd[2];

	commands = ft_split_commands(input, "|");
	here_doc(&vars, commands);
	i = 0;
	vars.p0 = 0;
	while (commands[i])
	{
		first_process(&vars, env, pipe_fd, &commands[i]);
		i++;
	}
	close(pipe_fd[0]);
	while (i-- > 0)
		wait(NULL);
	if (commands)
		ft_free(commands);
	if (input)
		free(input);
	input = NULL;
}

// rl_catch_signals = 0; // Disables the default behavior of SIGINT and SIGQUIT
// rl_set_signals(); // Tells readline to ignore the default behaviour of those
// signals and respect the ones we set in signal_handler()
int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	rl_set_signals();
	while (1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
		input = readline("myshell> ");
		if (!input)
		{
			printf("exit\n");
			rl_clear_history();
			return (0);
		}
		if (ft_strlen(input) != 0)
			add_history(input);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, custom_handle_signal);
		if (ft_strlen(input) != 0)
			minishell(input, env);
	}
	return (0);
}
