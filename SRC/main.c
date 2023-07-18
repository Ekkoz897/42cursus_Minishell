/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/07/18 13:16:47 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns i so that the processes dont interrupt each other (while loop)
int	minishell_helper(char *input, char **env, t_vars *vars,
		char **commands)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	commands = ft_split_commands(input, "|");
	if (check_cd_ex_uns(commands, vars))
	{
		ft_free_vars(vars);
		ft_free(commands);
		return (0);
	}
	here_doc(vars, commands);
	i = 0;
	vars->p0 = 0;
	while (commands[i])
	{
		first_process(vars, env, &commands[i], &j);
		(i)++;
	}
	return (i);
}

void	minishell(char *input, char **env, t_vars *vars)
{
	char	**commands;
	int		i;

	i = 0;
	commands = NULL;
	i = minishell_helper(input, env, vars, commands);
	if (i == 0)
		return ;
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

// rl_catch_signals = 0; // Disables the default behavior of SIGINT and SIGQUIT
// rl_set_signals(); // Tells readline to ignore the default behaviour of those
// signals and respect the ones we set in signal_handler()
void	setup_shell(t_vars *vars, char **env)
{
	rl_catch_signals = 0;
	rl_set_signals();
	ft_vars_init(vars);
	copy_environ(env, vars);
}

void	run_shell(t_vars *vars, char **env)
{
	char	*input;

	while (1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
		input = readline("myshell> ");
		if (!ft_exit_ctrl_d(input))
		{
			ft_free_vars(vars);
			break ;
		}
		if (ft_strlen(input) != 0)
			add_history(input);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, custom_handle_signal);
		if (ft_strlen(input) != 0)
			minishell(input, env, vars);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	(void)ac;
	(void)av;
	setup_shell(&vars, env);
	run_shell(&vars, env);
	return (0);
}
