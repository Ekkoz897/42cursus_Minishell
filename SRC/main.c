/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: apereira <apereira@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/23 13:42:14 by apereira		  #+#	#+#			 */
/*   Updated: 2023/07/17 11:24:33 by apereira		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"


//Creates a temporary fd to 
void	process_heredoc(t_vars *vars, char *doc_file, int fd)
{
	char	*str;

	write(1, "> ", 2);
	str = get_next_line(0);
	while (ft_strncmp(str, doc_file, ft_strlen(str)) != 0)
	{
		write(fd, str, ft_strlen(str));
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

void	open_doc_file(t_vars *vars, char *doc_file, int *j)
	{
	int	id;

	vars->here_doc_fd[*j] = open(vars->temp, O_CREAT | O_TRUNC \
		| O_RDWR, 0000644);
	if (vars->here_doc_fd[*j] == -1)
		perror(vars->temp);
	id = fork();
	if (id == 0)
		process_heredoc(vars, doc_file, vars->here_doc_fd[*j]);
	wait(NULL);
	free(doc_file);
	vars->here_doc_fd[*j] = open(vars->temp, O_RDONLY, 0000644);
}

void	open_doc(t_vars *vars, char *commands, int *j)
	{
	char	*doc_file;
	int		i;

	i = 0;
	commands = ft_strchr(commands, '<');
	commands += 2;
	while (*commands == ' ' || *commands == '	')
		commands++;
	while (commands[i] != '<' && commands[i] != '>' && commands[i] != ' ' \
		&& commands[i] != '	' && commands[i])
		i++;
	doc_file = ft_strndup(commands, i);
	vars->temp = doc_file;
	doc_file = ft_strjoin(doc_file, "\n");
	open_doc_file(vars, doc_file, j);
}

void	handle_heredoc(t_vars *vars, char *tmp, int *j)
{
	while (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
	{
		open_doc(vars, tmp, j);
		tmp = ft_strchr(tmp, '<') + 2;
		if (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
		{
			close(vars->here_doc_fd[*j]);
			unlink(vars->temp);
			free(vars->temp);
		}
	}
}

void	open_doc(t_vars *vars, char *commands, int *j)
	{
	char	*doc_file;
	int		i;

	i = 0;
	commands = ft_strchr(commands, '<');
	commands += 2;
	while (*commands == ' ' || *commands == '	')
		commands++;
	while (commands[i] != '<' && commands[i] != '>' && commands[i] != ' ' \
		&& commands[i] != '	' && commands[i])
		i++;
	doc_file = ft_strndup(commands, i);
	vars->temp = doc_file;
	doc_file = ft_strjoin(doc_file, "\n");
	open_doc_file(vars, doc_file, j);
}

void	handle_heredoc(t_vars *vars, char *tmp, int *j)
{
	while (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
	{
		open_doc(vars, tmp, j);
		tmp = ft_strchr(tmp, '<') + 2;
		if (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
		{
			close(vars->here_doc_fd[*j]);
			unlink(vars->temp);
			free(vars->temp);
		}
	}
}

//Searches the commands matrix for '<<'
//and calls open_doc
void	here_doc(t_vars *vars, char **commands)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		if (ft_strrchr(commands[i], '<') && *(ft_strrchr(commands[i], '<') - 1) \
			== '<')
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
		handle_heredoc(vars, tmp, &j);
		j++;
		i++;
	}
}


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
