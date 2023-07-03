/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/07/03 12:31:18 by miandrad         ###   ########.fr       */
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
	str = NULL;
	commands = ft_strchr(commands, '<');
	commands += 2;
	while (*commands == ' ' || *commands == '	')
		commands++;
	while (commands[i] != '<' && commands[i] != '>' && commands[i] != ' ' && commands[i] != '	' && commands[i])
		i++;
	doc_file = ft_strndup(commands, i);
	vars->temp = doc_file;
	doc_file = ft_strjoin(doc_file, "\n");
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
			free(str);
			write(1, "> ", 2);
			str = get_next_line(0);
		}
		free(str);
		str = NULL;
		get_next_line(-1);
		free(doc_file);
		ft_free_vars(vars);
		exit(0);
	}
	wait(NULL);
	free(doc_file);
	vars->here_doc_fd[*j] = open(vars->temp, O_RDONLY, 0000644);
}

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
	vars->here_doc_fd = malloc(sizeof(char) * j + 1);
	vars->here_doc_fd[j] = '\0';
	i = 0;
	j = 0;
	while (commands[i])
	{
		tmp = commands[i];
		while (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
		{
			open_doc(vars, tmp, &j);
			tmp = ft_strchr(tmp, '<') + 2;
			if (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
			{
				close(vars->here_doc_fd[j]);
				unlink(vars->temp);
				free(vars->temp);
			}
		}
		j++;
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
	int		j;

	j = 0;
	commands = ft_split_commands(input, "|");
	here_doc(vars, commands);
	i = 0;
	vars->p0 = 0;
	while (commands[i])
	{
		first_process(vars, env, &commands[i], &j);
		i++;
	}
	close(vars->pipe_fd[0]);
	while (i-- > 0)
		wait(NULL);
	if (commands)
		ft_free(commands);
	if (input)
		free(input);
	ft_free_vars(vars);
	input = NULL;
}

void	ft_vars_init(t_vars *vars)
{
	vars->here_doc_fd = NULL;
	vars->my_environ = NULL;
	vars->cmd2_flags = NULL;
	vars->cmd2_path = NULL;
	vars->cmd_flags = NULL;
	vars->cmd1_path = NULL;
	vars->temp = NULL;
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->cmd_flags)
	{	
		ft_free(vars->cmd_flags);
		vars->cmd_flags = NULL;
	}
	if (vars->my_environ)
	{	
		ft_free(vars->my_environ);
		vars->my_environ = NULL;
	}
	if (vars->here_doc_fd)
	{
		free(vars->here_doc_fd);
		vars->here_doc_fd = NULL;
	}
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
	ft_vars_init(&vars);
	vars.my_environ = copy_environ(env);
	while (1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
		input = readline("myshell> ");
		if (!ft_exit_ctrl_d(input))
		{
			ft_free_vars(&vars);
			return (0);
		}
		if (ft_strlen(input) != 0)
			add_history(input);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, custom_handle_signal);
		if (ft_strlen(input) != 0)
			minishell(input, env, &vars);
	}
	return (0);
}
