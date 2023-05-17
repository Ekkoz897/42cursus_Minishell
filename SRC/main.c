/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/05/17 16:16:30 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_doc(t_vars *vars, char *commands, int *j)
{
	char	*doc_file;
	char	*str;
	int		i;
	int		id;

	i = 0;
	commands = ft_strchr(commands, '<');
	commands += 2;
	while (*commands == ' ' || *commands == '	')
		commands++;
	while (commands[i] != '<' && commands[i] != '>' && commands[i] != ' ' && commands[i] != '	' && commands[i])
		i++;
	doc_file = ft_strndup(commands, i);
	vars->temp = doc_file;
	doc_file = ft_strjoin(doc_file, "\n");
	ft_printf("%s\n", vars->temp);
	vars->here_doc_fd[*j] = open(vars->temp, O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (vars->here_doc_fd[*j] == -1)
		perror(vars->temp);
	id = fork();
	if (id == 0)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		while (ft_strncmp(str, doc_file, ft_strlen(str)) != 0)
		{
			write(vars->here_doc_fd[*j], str, ft_strlen(str));
			ft_printf("%i\n", vars->here_doc_fd[*j]);
			free(str);
			write(1, "> ", 2);
			str = get_next_line(0);
		}
		free(str);
		exit(0);
	}
	wait(NULL);
	close(vars->here_doc_fd[*j]);
	vars->here_doc_fd[*j] = open(vars->temp, O_RDONLY, 0000644);
	(*j)++;
}

// Comentei "// tmp = tmp + ft_strchr(tmp, '<');" porque nao compilava
void	here_doc(t_vars *vars, char **commands)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		if (ft_strrchr(commands[i], '<') \
			&& *(ft_strrchr(commands[i], '<') - 1) == '<')
			j++;
		i++;
	}
	vars->here_doc_fd = malloc(sizeof(int) * j + 1);
	vars->here_doc_fd[j] = '\0';
	i = 0;
	j = 0;
	while (commands[i])
	{
		tmp = commands[i];
		while (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
		{
			open_doc(vars, tmp, &j);
			if (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
			{
				close(vars->here_doc_fd[j]);
				unlink(vars->temp);
				free(vars->temp);
				tmp = ft_strchr(tmp, '<') + 2;
			}
			ft_printf("%s\n", tmp);
		}
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
void	minishell(char *input, char **env, t_vars *vars)
{
	char	**commands;
	int		i;
	int		pipe_fd[2];

	commands = ft_split_commands(input, "|");
	if (check_if_builtin(commands, vars))
		return ;
	here_doc(vars, commands);
	i = 0;
	vars->p0 = 0;
	while (commands[i])
	{
		first_process(vars, env, pipe_fd, &commands[i]);
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
	t_vars	vars;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	rl_set_signals();
	vars.my_environ = copy_environ(env);
	while (1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
		input = readline("myshell> ");
		if (!ft_exit(input))
			return (0);
		if (ft_strlen(input) != 0)
			add_history(input);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, custom_handle_signal);
		if (ft_strlen(input) != 0)
			minishell(input, env, &vars);
	}
	ft_free(vars.my_environ);
	return (0);
}
