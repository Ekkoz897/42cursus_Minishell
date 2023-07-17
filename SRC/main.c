/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:42:14 by apereira          #+#    #+#             */
/*   Updated: 2023/07/17 11:42:54 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell(char *input, char **env, t_vars *vars)
{
	char	**commands;
	int		i;
	int		j;

	j = 0;
	commands = ft_split_commands(input, "|");
	if (check_cd_ex_uns(commands, vars))
	{
		ft_free_vars(vars);
		ft_free(commands);
		return ;
	}
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
	copy_environ(env, &vars);
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
